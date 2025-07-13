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
    if (!m_camGO) return;  // sécurité

    SHORT state = GetAsyncKeyState(VK_RBUTTON);
    bool pressed = (state & 0x8000) != 0;
    if (pressed && !m_rotating)
    {
        m_rotating = true;
        SetCapture(m_hWnd);
        ShowCursor(FALSE);
        GetCursorPos(&m_lastMouse);
    }
    else if (!pressed && m_rotating)
    {
        m_rotating = false;
        ReleaseCapture();
        ShowCursor(TRUE);
    }

    if (m_rotating)
    {
        POINT cur; GetCursorPos(&cur);
        int dx = cur.x - m_lastMouse.x;
        int dy = cur.y - m_lastMouse.y;

        m_yaw += dx * m_sensitivity;
        m_pitch += dy * m_sensitivity;
        m_pitch = std::clamp(m_pitch, -89.f, +89.f);

        // Applique la rotation sur le parent
        if (m_parentGO)
        {
            auto* pt = m_parentGO->GetComponent<TransformComponent>();
            pt->SetRotation(m_pitch, m_yaw, 0.f);
            pt->dirty = true;
        }

        SetCursorPos(m_lastMouse.x, m_lastMouse.y);
    }
}