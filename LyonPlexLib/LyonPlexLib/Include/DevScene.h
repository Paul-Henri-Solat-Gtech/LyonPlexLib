#pragma once
class DevScene : public Scene
{
public:
	void Start() override;
	void Update(float deltatime) override;
	void Release() override;

private:
	GameObject m_placingModule;
	GameObject m_camera;

	int m_newIdGM;
	int m_camSpeed, m_camWalkSpeed, m_camRunSpeed;
 
	std::string m_lastPlacedGmName;
	XMFLOAT3 m_lastPlacedGmPos;

	// Membres pour l�orbite
	bool   m_orbiting = false;
	POINT  m_lastMousePos = { 0,0 };
	
	//float  m_orbitAngle = 0.0f;    // en degr�s
	float  m_orbitYaw = 0.0f;    // angle horizontal en degr�s
	float  m_orbitPitch = 0.0f;    // angle vertical en degr�s
	
	float  m_orbitRadius = 5.0f;   // d�j� pr�sent
	float  m_orbitHeight = 1.0f;   // peut rester pour initial fallback, mais on recalcule via pitch
	float  m_sensitivity = 0.2f;   // degr�s par pixel horizontal
	HWND   m_hWnd = nullptr;       // handle de la fen�tre, � initialiser
};

