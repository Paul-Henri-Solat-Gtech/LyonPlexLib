#include "pch.h"
#include "Button.h"

Button::Button(Scene* scene, HWND windowHandle)
{
    mp_scene = scene;
    m_windowHandle = windowHandle;

    Init("btStart", mp_scene->GetEcsManager(), mp_scene, TYPE_2D, true);
    //InitGameObj(mp_scene->GetEcsManager(), mp_scene);

    SetMesh(MESHES::LOCAL_SQUARE);
    SetTexture(TEXTURES::start);

    RECT renderZone;
    GetClientRect(mp_scene->GetSceneManager()->GetGameManager()->GetRenderingManager().GetGraphicsDevice()->GetWindow(), &renderZone);
    UINT renderWidth = renderZone.right - renderZone.left;
    UINT renderHeight = renderZone.bottom - renderZone.top;

    SetPosition({ (float)renderWidth * 0.5f, (float)renderHeight * 0.5f, 0.0f });
    SetScale({ (float)renderWidth * 0.4f, (float)renderHeight * 0.15f, 0.0f });
    GetComponent<TransformComponent>()->AddRotation(0, 0, 180);

    //SetPosition({ 0, 0, 0 });
    //SetScale({ 50, 50, 0 });
}

void Button::Initialize(HWND windowHandle, const std::string& name, ECSManager* ecsManager, Scene* scene, DimensionalType type, bool useMesh)
{
    //m_windowHandle = windowHandle;
    //Init(name, ecsManager, scene, type, useMesh);
}

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
    auto pos = GetPosition(); // XMFLOAT3
    auto scale = GetScale();    // XMFLOAT3

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


