#pragma once
class FpsCamera
{
public:
    /// Crée la camera sous le nom donné, mais *ne la parent pas*
    void Init(GameObject& camGO, HWND hWnd);

    /// Handle la rotation souris et pivote le parent via TransformComponent
    void Update(float deltaTime);

    void ForceHideCursor();
    void ForceShowCursor();
    void CenterCursorInWindow();

    void SetAlwaysActive(bool active);

    /// Pour récupérer le nom que la caméra a enregistré
    const std::string& GetName() const { return m_camName; };

private:
    std::string  m_camName;
    GameObject*   m_camGO = nullptr; // ex: camera scene
    HWND         m_hWnd = nullptr;

    bool m_alwaysActive = false;

    float        m_yaw = -90.f;
    float        m_pitch = 0.f;
    float        m_sensitivity = 0.15f;
    bool         m_rotating = false;
    POINT        m_lastMouse = { 0,0 };
};

