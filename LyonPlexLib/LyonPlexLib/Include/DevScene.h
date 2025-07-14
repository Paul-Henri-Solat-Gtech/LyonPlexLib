#pragma once
class DevScene : public Scene
{
public:
	void Start() override;
	void Update(float deltatime) override;
	void Release() override;

	void CameraDevSystem(float deltatime);

	std::string Float2Str(float value);

	std::string RoundValueStr(float value);
	float RoundValue(float value, int roundTo = 1);

	int ComputeGridStep(float scale);

private:
	GameObject m_placingModule;
	GameObject m_camera;

	int m_newIdGM;
	int m_camSpeed, m_camWalkSpeed, m_camRunSpeed, m_scaleSpeed, m_scaleNormalSpeed, m_scaleFastSpeed;

	std::string m_lastPlacedGmName;
	XMFLOAT3 m_lastPlacedGmPos;

	//quadrillage
	bool m_QuadrillageModeIsOn;
	bool m_QuadrillageUnitaireIsOn;

	// Camera
	// Membres pour lorbite
	bool   m_orbiting = false;
	POINT  m_lastMousePos = { 0,0 };

	float  m_orbitYaw = 0.0f;      // angle horizontal en degree
	float  m_orbitPitch = 0.0f;    // angle vertical en degree

	float  m_orbitRadius = 5.0f;   // present
	float  m_orbitHeight = 1.0f;   // peut rester pour initial fallback, mais on recalcule via pitch
	float  m_sensitivity = 0.2f;   // degree par pixel horizontal
	HWND   m_hWnd = nullptr;       // handle de la fenetre, initialiser
};

