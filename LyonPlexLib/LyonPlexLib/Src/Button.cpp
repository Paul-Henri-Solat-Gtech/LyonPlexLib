#include "pch.h"
#include "Button.h"

//Button::Button(Scene* scene, HWND windowHandle, uint32_t texture, std::string btnName)
//{
//    mp_scene = scene;
//    m_windowHandle = windowHandle;
//
//    Init(btnName, mp_scene->GetEcsManager(), mp_scene, TYPE_2D, true);
//    //InitGameObj(mp_scene->GetEcsManager(), mp_scene);
//
//    SetMesh(MESHES::LOCAL_SQUARE);
//    SetTexture(texture);
//
//    RECT renderZone;
//    GetClientRect(mp_scene->GetSceneManager()->GetGameManager()->GetRenderingManager().GetGraphicsDevice()->GetWindow(), &renderZone);
//    UINT renderWidth = renderZone.right - renderZone.left;
//    UINT renderHeight = renderZone.bottom - renderZone.top;
//
//    SetPosition({ (float)renderWidth * 0.5f, (float)renderHeight * 0.5f, 0.0f });
//    SetScale({ (float)renderWidth * 0.4f, (float)renderHeight * 0.15f, 0.0f });
//    GetComponent<TransformComponent>()->AddRotation(0, 0, 180);
//
//    //SetPosition({ 0, 0, 0 });
//    //SetScale({ 50, 50, 0 });
//}
//
//void Button::Initialize(HWND windowHandle, const std::string& name, ECSManager* ecsManager, Scene* scene, DimensionalType type, bool useMesh)
//{
//    //m_windowHandle = windowHandle;
//    //Init(name, ecsManager, scene, type, useMesh);
//}
//
//bool Button::GetMouseOnBtn()
//{
//    // 0)
//    //if (!m_gameObjectBtn)
//    //    return false;
//
//    // 1) R馗up鑽e la position souris en coordonn馥s client
//    POINT p;
//    GetCursorPos(&p);
//    ScreenToClient(m_windowHandle, &p);
//
//    // 2) R馗up鑽e la position et la taille du GameObject
//    auto pos = GetPosition(); // XMFLOAT3
//    auto scale = GetScale();    // XMFLOAT3
//
//    // On consid鑽e que 'pos' est le centre ; on calcule les bords
//    float halfW = scale.x * 0.5f;
//    float halfH = scale.y * 0.5f;
//    float left = pos.x - halfW;
//    float right = pos.x + halfW;
//    float top = pos.y - halfH;
//    float bottom = pos.y + halfH;
//
//    // 3) Teste si la souris est dans le rectangle
//    return (p.x >= left && p.x <= right &&
//        p.y >= top && p.y <= bottom);
//}
//
//bool Button::GetBtnIsClicked()
//{
//    // 0)
//    //if (!m_gameObjectBtn)
//    //    return false;
//
//    // On saute si la souris n'est pas sur le bouton
//    if (!GetMouseOnBtn())
//        return false;
//
//    // Ici tu peux utiliser ton InputManager ou la Win32 directement
//    // Exemple Win32 : VK_LBUTTON pour le clic gauche
//    SHORT state = GetAsyncKeyState(VK_LBUTTON);
//    bool clicked = (state & 0x8000) != 0;
//
//    return clicked;
//}

Button::Button(Scene* scene, HWND windowHandle, uint32_t texture, std::string btnName)
{
    mp_scene = scene;
    m_windowHandle = windowHandle;

    ECSManager* ecs = nullptr;
    if (mp_scene) ecs = mp_scene->GetEcsManager();

    // Safe init: pass nullptr if ecs not available - Init should handle it gracefully
    Init(btnName, ecs, mp_scene, TYPE_2D, true);

    SetMesh(MESHES::LOCAL_SQUARE);
    SetTexture(texture);

    // Resolve a HWND to query client size (prefer provided handle, fallback to scene window)
    HWND hwnd = ResolveHWND();
    RECT renderZone{ 0,0,800,600 };
    if (IsWindow(hwnd)) {
        GetClientRect(hwnd, &renderZone);
    }

    UINT renderWidth = renderZone.right - renderZone.left;
    UINT renderHeight = renderZone.bottom - renderZone.top;

    // prepare desired pos/scale in screen coordinates
    XMFLOAT3 desiredPos = { (float)renderWidth * 0.5f, (float)renderHeight * 0.5f, 0.0f };
    XMFLOAT3 desiredScale = { (float)renderWidth * 0.4f, (float)renderHeight * 0.15f, 0.0f };

    // Try to apply these to the GameObject transform if available.
    // SetPosition/SetScale call into ECS; protect by caching the TransformComponent pointer first.
    m_cachedTransform = GetComponent<TransformComponent>();
    if (m_cachedTransform) {
        // if transform exists, use GameObject API (keeps engine state consistent)
        SetPosition(desiredPos);
        SetScale(desiredScale);
        // try safe rotation add if transform pointer valid
        m_cachedTransform->AddRotation(0, 0, 180);
    }
    else {
        // otherwise store values locally so the button logic can use them until transform becomes available
        m_cachedPos = desiredPos;
        m_cachedScale = desiredScale;
    }
}

void Button::Initialize(HWND windowHandle, const std::string& name, ECSManager* ecsManager, Scene* scene, DimensionalType type, bool useMesh)
{
    // kept for API compatibility, do nothing here - constructor handles init
    (void)windowHandle;
    (void)name;
    (void)ecsManager;
    (void)scene;
    (void)type;
    (void)useMesh;
}

void Button::Release()
{
    // nothing specific for now; if you allocate resources in future, free them here
}

HWND Button::ResolveHWND() const
{
    if (IsWindow(m_windowHandle)) return m_windowHandle;
    if (mp_scene) {
        SceneManager* sm = mp_scene->GetSceneManager();
        if (sm) {
            HWND sceneHwnd = sm->GetWindow();
            if (IsWindow(sceneHwnd)) return sceneHwnd;
        }
    }
    return nullptr;
}

bool Button::GetMouseOnBtn()
{
    // Ensure we have a valid HWND to convert the cursor coordinates.
    HWND hwnd = ResolveHWND();
    POINT p{};
    if (!GetCursorPos(&p)) return false;
    if (IsWindow(hwnd)) {
        if (!ScreenToClient(hwnd, &p)) return false;
    }
    // If no valid hwnd, we assume screen coords already match our cached coords (unlikely but safe)

    // Ensure transform is cached; try to obtain it once if not
    if (!m_cachedTransform) {
        m_cachedTransform = GetComponent<TransformComponent>();
        if (m_cachedTransform) {
            // apply any cached pos/scale to real transform now (keeps engine consistent)
            SetPosition(m_cachedPos);
            SetScale(m_cachedScale);
            m_cachedTransform->AddRotation(0, 0, 180);
        }
    }

    XMFLOAT3 pos;
    XMFLOAT3 scale;

    if (m_cachedTransform) {
        pos = m_cachedTransform->position;
        scale = m_cachedTransform->scale;
    }
    else {
        // fallback to cached values (safe)
        pos = m_cachedPos;
        scale = m_cachedScale;
    }

    float halfW = scale.x * 0.5f;
    float halfH = scale.y * 0.5f;
    float left = pos.x - halfW;
    float right = pos.x + halfW;
    float top = pos.y - halfH;
    float bottom = pos.y + halfH;

    return (p.x >= left && p.x <= right && p.y >= top && p.y <= bottom);
}

bool Button::GetBtnIsClicked()
{
    if (!GetMouseOnBtn()) return false;

    SHORT state = GetAsyncKeyState(VK_LBUTTON);
    bool clicked = (state & 0x8000) != 0;

    return clicked;
}
