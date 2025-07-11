#pragma once
class FreeCamera
{
public:

	void Init(ECSManager* ecsManager, HWND hWnd);
	void Update(float deltatime);

    GameObject& GetCamGameObject() { return m_camGM; };
    std::string GetCamName() { return m_camName; };

private:

	GameObject   m_camGM;
    std::string  m_camName;

    HWND         m_hWnd = nullptr;
    float        m_yaw = 0.f;      // en degrés
    float        m_pitch = 0.f;      // en degrés
    float        m_sensitivity = 0.2f;   // rotation souris
    float        m_walkSpeed = 3.f;      // vitesse normale
    float        m_runSpeed = 6.f;      // vitesse avec shift
    bool         m_rotating = false;
    POINT        m_lastMouse = { 0,0 };

    bool m_pressed;
};