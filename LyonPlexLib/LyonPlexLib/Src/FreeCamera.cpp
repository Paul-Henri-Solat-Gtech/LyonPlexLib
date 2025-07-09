#include "pch.h"
#include "FreeCamera.h"

void FreeCamera::Init(ECSManager* ecsManager, HWND hWnd)
{
	m_hWnd = hWnd;

	m_camGM.Init("FreeCamera", ecsManager, TYPE_3D, false);
	m_camGM.AddComponent<CameraComponent>(new CameraComponent());
	
	// Position initiale
	m_camGM.SetPosition({ 0.f, 2.f, -5.f });
	// Orientation initiale (face vers +Z)
	m_yaw = 0.f;
	m_pitch = 0.f;

    m_pressed = true;
}

void FreeCamera::Update(float deltatime)
{
    // --- 1) Gérer la rotation avec clic droit + souris ---
    SHORT state = GetAsyncKeyState(VK_RBUTTON);
    //bool pressed = (state & 0x8000) != 0;

    if (m_pressed && !m_rotating)
    {
        m_rotating = true;
        SetCapture(m_hWnd);
        ShowCursor(FALSE);
        GetCursorPos(&m_lastMouse);
    }
    else if (!m_pressed && m_rotating)
    {
        ShowCursor(TRUE);
        m_rotating = false;
        ReleaseCapture();
    }

    if (m_rotating)
    {
        POINT cur; GetCursorPos(&cur);
        int dx = cur.x - m_lastMouse.x;
        int dy = cur.y - m_lastMouse.y;
        m_yaw += dx * m_sensitivity;
        m_pitch += -dy * m_sensitivity;
        m_pitch = std::clamp(m_pitch, -89.0f, +89.0f);
        // recentre la souris
        SetCursorPos(m_lastMouse.x, m_lastMouse.y);
    }

    // Applique la nouvelle orientation
    XMVECTOR q = XMQuaternionRotationRollPitchYaw(XMConvertToRadians(m_pitch), XMConvertToRadians(m_yaw), 0.f );
    XMFLOAT4 qf;
    XMStoreFloat4(&qf, q);
    m_camGM.SetRotation(qf);
    m_camGM.GetComponent<TransformComponent>()->dirty = true;

    // --- 2) Gérer le mouvement WASD + vertical ---
    // Calcule forward/right à partir du quaternion
    XMMATRIX rotMat = XMMatrixRotationQuaternion(q);
    XMVECTOR forward = XMVector3Normalize(XMVector3TransformNormal(XMVectorSet(0, 0, 1, 0), rotMat));
    // on ne veut pas lever/descendre quand on avance
    forward = XMVectorSetY(forward, 0.f);
    forward = XMVector3Normalize(forward);

    XMVECTOR right = XMVector3Normalize(XMVector3Cross(XMVectorSet(0, 1, 0, 0), forward));

    XMVECTOR move = XMVectorZero();
    if (InputManager::GetKeyIsPressed('Z')) move += forward;
    if (InputManager::GetKeyIsPressed('S')) move -= forward;
    if (InputManager::GetKeyIsPressed('D')) move += right;
    if (InputManager::GetKeyIsPressed('Q')) move -= right;
    if (InputManager::GetKeyIsPressed(VK_SPACE))   move += XMVectorSet(0, 1, 0, 0);
    if (InputManager::GetKeyIsPressed(VK_CONTROL)) move -= XMVectorSet(0, 1, 0, 0);
    if (InputManager::GetKeyIsReleased(VK_ESCAPE)) 
    {
        if (m_pressed) 
        {
            m_pressed = false;
        }
        else
        {
            m_pressed = true;
        }
        
    }

    // vitesse (shift pour courir)
    float speed = InputManager::GetKeyIsPressed(VK_SHIFT) ? m_runSpeed : m_walkSpeed;

    if (!XMVector3Equal(move, XMVectorZero()))
    {
        move = XMVector3Normalize(move) * (speed * deltatime);
        // applique sur la position
        XMFLOAT3 pos = m_camGM.GetPosition();
        XMVECTOR  p = XMLoadFloat3(&pos) + move;
        XMStoreFloat3(&pos, p);
        m_camGM.SetPosition(pos);
        m_camGM.GetComponent<TransformComponent>()->dirty = true;
    }
}
