#include "pch.h"
#include "Button.h"

void Button::Init(GameObject gmButton, HWND windowHandle)
{
	m_gameObjectBtn = gmButton;
    m_windowHandle = windowHandle;
}

//void Button::Release()
//{
//    m_gameObjectBtn = nullptr;
//}

bool Button::GetMouseOnBtn()
{
    // 0)
    //if (!m_gameObjectBtn)
    //    return false;

    // 1) Récupère la position souris en coordonnées client
    POINT p;
    GetCursorPos(&p);
    ScreenToClient(m_windowHandle, &p);

    // 2) Récupère la position et la taille du GameObject
    auto pos = m_gameObjectBtn.GetPosition(); // XMFLOAT3
    auto scale = m_gameObjectBtn.GetScale();    // XMFLOAT3

    // On considère que 'pos' est le centre ; on calcule les bords
    float halfW = scale.x * 0.5f;
    float halfH = scale.y * 0.5f;
    float left = pos.x - halfW;
    float right = pos.x + halfW;
    float top = pos.y - halfH;
    float bottom = pos.y + halfH;

    // 3) Teste si la souris est dans le rectangle
    return (p.x >= left && p.x <= right &&
        p.y >= top && p.y <= bottom);
}

bool Button::GetBtnIsClicked()
{
    // 0)
    //if (!m_gameObjectBtn)
    //    return false;

    // On saute si la souris n'est pas sur le bouton
    if (!GetMouseOnBtn())
        return false;

    // Ici tu peux utiliser ton InputManager ou la Win32 directement
    // Exemple Win32 : VK_LBUTTON pour le clic gauche
    SHORT state = GetAsyncKeyState(VK_LBUTTON);
    bool clicked = (state & 0x8000) != 0;

    return clicked;
}


