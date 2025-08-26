#include "FpsCamera.h"
#include "pch.h"
#include "FpsCamera.h"

void FpsCamera::Init(GameObject& camGO, HWND hWnd)
{
    m_camGO = &camGO;         // on ne recrée pas, on pointe juste dessus
    m_hWnd = hWnd;
    // initialise yaw/pitch, position locale…
    auto* t = camGO.GetComponent<TransformComponent>();
    t->position = { 0,1.7f,0.2f };
    t->dirty = true;
}

void FpsCamera::Update(float deltaTime)
{
    if (!m_camGO) return;

    // si on n'est pas en alwaysActive, on suit le clic droit comme avant
    if (!m_alwaysActive)
    {
        SHORT state = GetAsyncKeyState(VK_RBUTTON);
        bool pressed = (state & 0x8000) != 0;
        if (pressed && !m_rotating)
        {
            m_rotating = true;
            SetCapture(m_hWnd);
            if (IsWindow(m_hWnd))
            {
                RECT rc; GetClientRect(m_hWnd, &rc);
                POINT tl{ rc.left, rc.top }, br{ rc.right, rc.bottom };
                ClientToScreen(m_hWnd, &tl); ClientToScreen(m_hWnd, &br);
                RECT clip{ tl.x, tl.y, br.x, br.y };
                ClipCursor(&clip);
            }
            CenterCursorInWindow();
            ForceHideCursor();
        }
        else if (!pressed && m_rotating)
        {
            m_rotating = false;
            ReleaseCapture();
            ClipCursor(nullptr);
            ForceShowCursor();
        }
    }

    if (m_rotating)
    {
        POINT cur; GetCursorPos(&cur);
        int dx = cur.x - m_lastMouse.x;
        int dy = cur.y - m_lastMouse.y;

        m_yaw += dx * m_sensitivity;
        m_pitch += dy * m_sensitivity;
        m_pitch = std::clamp(m_pitch, -89.f, +89.f);

        if (m_parentGO)
        {
            auto* pt = m_parentGO->GetComponent<TransformComponent>();
            if (pt) {
                pt->SetRotation(m_pitch, m_yaw, 0.f);
                pt->dirty = true;
            }
        }

        // recentre le curseur à la position de référence (milieu)
        CenterCursorInWindow();
    }
}

// Force hide: appelle ShowCursor(FALSE) jusqu'à ce que le compteur interne devienne négatif
void FpsCamera::ForceHideCursor()
{
    // appelle ShowCursor(FALSE) tant que la valeur retournée est >= 0
    // (cette boucle finit par cacher le curseur même si d'autres parties ont augmenté le compteur)
    while (ShowCursor(FALSE) >= 0) { /* loop */ }
}

// Force show: appelle ShowCursor(TRUE) jusqu'à ce que le compteur devienne >= 0
void FpsCamera::ForceShowCursor()
{
    while (ShowCursor(TRUE) < 0) { /* loop */ }
}

// Centre la souris dans la fenêtre client et convertit en coords écran
void FpsCamera::CenterCursorInWindow()
{
    if (!m_hWnd || !IsWindow(m_hWnd)) return;
    RECT rc;
    GetClientRect(m_hWnd, &rc);
    POINT center{ (rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2 };
    ClientToScreen(m_hWnd, &center);
    SetCursorPos(center.x, center.y);
    m_lastMouse = center;
}

// SetAlwaysActive : active/désactive le mode FPS permanent
void FpsCamera::SetAlwaysActive(bool active)
{
    // no-op si pas de changement
    if (m_alwaysActive == active) return;
    m_alwaysActive = active;

    if (active)
    {
        // start rotating: capture + clip + hide + center
        if (!m_rotating)
        {
            m_rotating = true;
            // capture les messages souris pour la fenêtre
            SetCapture(m_hWnd);

            // limite le curseur au rectangle client de la fenêtre
            if (IsWindow(m_hWnd))
            {
                RECT rc;
                GetClientRect(m_hWnd, &rc);
                POINT topLeft{ rc.left, rc.top }, bottomRight{ rc.right, rc.bottom };
                ClientToScreen(m_hWnd, &topLeft);
                ClientToScreen(m_hWnd, &bottomRight);
                RECT clipRect{ topLeft.x, topLeft.y, bottomRight.x, bottomRight.y };
                ClipCursor(&clipRect);
            }

            CenterCursorInWindow();

            // masquer de façon fiable
            ForceHideCursor();
        }
    }
    else
    {
        // stop rotating: release capture + unclip + show
        if (m_rotating)
        {
            m_rotating = false;
            ReleaseCapture();
            ClipCursor(nullptr);       // libère le clip
            ForceShowCursor();         // rend le curseur visible de façon fiable
        }
    }
}