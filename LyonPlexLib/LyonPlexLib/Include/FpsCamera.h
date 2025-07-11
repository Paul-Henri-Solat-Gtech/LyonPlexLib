#pragma once
class FpsCamera
{
public:
    /// Crée la camera sous le nom donné, mais *ne la parent pas*
    void Init(GameObject& camGO, HWND hWnd);

    /// Handle la rotation souris et pivote le parent via TransformComponent
    void Update(float deltaTime);

    /// Pour récupérer le nom que la caméra a enregistré
    const std::string& GetName() const { return m_camName; };
    void SetParentGO(GameObject& parent) { m_parentGO = &parent; };

private:
    std::string  m_camName;
    GameObject*   m_camGO = nullptr;
    GameObject* m_parentGO = nullptr;
    HWND         m_hWnd = nullptr;

    float        m_yaw = 0.f;
    float        m_pitch = 0.f;
    float        m_sensitivity = 0.15f;
    bool         m_rotating = false;
    POINT        m_lastMouse = { 0,0 };
};

