#include "pch.h"
#include "DevScene.h"

#undef max
#undef min
#include <algorithm>

void DevScene::Start()
{
	// R馗up駻er le HWND depuis SceneManager
	m_hWnd = mp_sceneManager->GetWindow();

	// Cr馥r le cube (placingModule)
	CreateGameObject("placingModule");
	m_placingModule = GetGameObjectByName("placingModule");
	m_placingModule.SetPosition({ 0, 0, 0 }); // par exemple au centre
	m_placingModule.SetTexture(TEXTURES::NOTEXTURE);

	// Cr馥r la cam駻a
	CreateGameObject("camera", TYPE_3D, false);
	m_camera = GetGameObjectByName("camera");
	m_camera.AddComponent<CameraComponent>(new CameraComponent());

	XMFLOAT3 cubePos = m_placingModule.GetPosition();
	XMFLOAT3 camPos = m_camera.GetPosition();
	float dx = camPos.x - cubePos.x;
	float dy = camPos.y - cubePos.y;
	float dz = camPos.z - cubePos.z;
	float radius = sqrtf(dx * dx + dy * dy + dz * dz);
	if (radius > 0.001f)
	{
		m_orbitRadius = radius;
		m_orbitYaw = XMConvertToDegrees(atan2f(dx, dz));
		m_orbitPitch = XMConvertToDegrees(asinf(dy / radius));
		m_orbitPitch = std::clamp(m_orbitPitch, -89.0f, +89.0f);
	}

	// Cr馥r le ground, etc.
	CreateGameObject("ground", 2, 3);
	GetGameObjectByName("ground").SetPosition({ 0, -2, 0 });
	GetGameObjectByName("ground").SetScale({ 50, 1, 50 });
	GetGameObjectByName("ground").SetTexture(TEXTURES::GRID);

	m_newIdGM = 0;
	m_camWalkSpeed = 3.f;
	m_camRunSpeed = 6.f;
	m_camSpeed = m_camWalkSpeed;

	m_scaleNormalSpeed = 1;
	m_scaleSpeed = 5;
	m_scaleSpeed = m_scaleNormalSpeed;

	OutputDebugStringA("\Quadrillage : ON \n");
	m_QuadrillageModeIsOn = true;
	m_QuadrillageUnitaireIsOn = true;
	// Test
}

void DevScene::Update(float deltatime)
{
	// Move (OLD)
	{
		/*if (InputManager::GetKeyIsPressed('Z'))
		{
			m_placingModule.GetComponent<TransformComponent>()->position.z += m_camSpeed * deltatime;
			m_placingModule.GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed('S'))
		{
			m_placingModule.GetComponent<TransformComponent>()->position.z -= m_camSpeed * deltatime;
			m_placingModule.GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed('Q'))
		{
			m_placingModule.GetComponent<TransformComponent>()->position.x -= m_camSpeed * deltatime;
			m_placingModule.GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed('D'))
		{
			m_placingModule.GetComponent<TransformComponent>()->position.x += m_camSpeed * deltatime;
			m_placingModule.GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed(VK_SPACE))
		{
			m_placingModule.GetComponent<TransformComponent>()->position.y += m_camSpeed * deltatime;
			m_placingModule.GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed(VK_CONTROL))
		{
			m_placingModule.GetComponent<TransformComponent>()->position.y -= m_camSpeed * deltatime;
			m_placingModule.GetComponent<TransformComponent>()->dirty = true;
		}*/
	}

	// Camera
	CameraDevSystem(deltatime);

	// Movements
	if (InputManager::GetKeyIsPressed(VK_SHIFT))
	{
		m_camSpeed = m_camRunSpeed;
		m_scaleSpeed = 5;
	}
	else
	{
		m_camSpeed = m_camWalkSpeed;
		m_scaleSpeed = 1;
	}

	// cam rotate(prototype)
	EnableMouseRotationFor(m_placingModule, 0.2f);

	// Rotate
	if (InputManager::GetKeyIsPressed(VK_RIGHT))
	{
		m_placingModule.GetComponent<TransformComponent>()->AddRotation(0.f, -100.f * 1, 0.f);
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed(VK_LEFT))
	{
		m_placingModule.GetComponent<TransformComponent>()->AddRotation(0.f, 100.f * 1, 0.f);
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed(VK_UP))
	{
		m_placingModule.GetComponent<TransformComponent>()->AddRotation(100.f * 1, 0.f, 0.f);
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsPressed(VK_DOWN))
	{
		m_placingModule.GetComponent<TransformComponent>()->AddRotation(-100.f * 1, 0.f, 0.f);
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}

	// Scale
	if (InputManager::GetKeyIsJustPressed(VK_ADD))
	{
		m_placingModule.GetComponent<TransformComponent>()->scale.x += m_scaleSpeed;
		m_placingModule.GetComponent<TransformComponent>()->scale.y += m_scaleSpeed;
		m_placingModule.GetComponent<TransformComponent>()->scale.z += m_scaleSpeed;
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsJustPressed(VK_SUBTRACT))
	{
		m_placingModule.GetComponent<TransformComponent>()->scale.x -= m_scaleSpeed;
		m_placingModule.GetComponent<TransformComponent>()->scale.y -= m_scaleSpeed;
		m_placingModule.GetComponent<TransformComponent>()->scale.z -= m_scaleSpeed;
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsJustPressed('R'))
	{
		m_placingModule.GetComponent<TransformComponent>()->scale.x += m_scaleSpeed;
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsJustPressed('T'))
	{
		m_placingModule.GetComponent<TransformComponent>()->scale.x -= m_scaleSpeed;
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsJustPressed('Y'))
	{
		m_placingModule.GetComponent<TransformComponent>()->scale.y += m_scaleSpeed;
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsJustPressed('U'))
	{
		m_placingModule.GetComponent<TransformComponent>()->scale.y -= m_scaleSpeed;
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsJustPressed('I'))
	{
		m_placingModule.GetComponent<TransformComponent>()->scale.z += m_scaleSpeed;
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}
	if (InputManager::GetKeyIsJustPressed('O'))
	{
		m_placingModule.GetComponent<TransformComponent>()->scale.z -= m_scaleSpeed;
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}

	// ChangeScene
	if (InputManager::GetKeyIsReleased('A'))
	{
		ChangeScene("MainMenuScene");
	}

	//Mode cadriage
	if (InputManager::GetKeyIsReleased('W'))
	{
		
		m_QuadrillageModeIsOn = !m_QuadrillageModeIsOn;
		if (m_QuadrillageModeIsOn)
			OutputDebugStringA("\Quadrillage : ON \n");
		else
			OutputDebugStringA("\Quadrillage : OFF \n");

	}
	//Mode cadriage round force a 1
	if (InputManager::GetKeyIsReleased('C'))
	{
		m_QuadrillageUnitaireIsOn = !m_QuadrillageUnitaireIsOn;
		if (m_QuadrillageUnitaireIsOn)
			OutputDebugStringA("\Quadrillage UNITAIRE : ON \n");
		else
			OutputDebugStringA("\Quadrillage UNITAIRE : OFF \n");
	}

	// Adding blocks (make a function in this scene)
	if (InputManager::GetKeyIsReleased(VK_LBUTTON))
	{
		auto& blocScale = m_placingModule.GetScale();
		float scaleMoy = 0;
		if (!m_QuadrillageUnitaireIsOn) scaleMoy = (blocScale.x + blocScale.y + blocScale.z) / 3;
		else scaleMoy = 1;

		/*if (blocScale.x > blocScale.y)
		{
			if (blocScale.x > blocScale.z)
			{
				scaleMax = blocScale.x;
			}
			else
			{
				scaleMax = blocScale.z;
			}
		}
		else if (blocScale.y > blocScale.z)
		{
			scaleMax = blocScale.y;

		}
		else scaleMax = blocScale.z;*/


		int   step = ComputeGridStep(scaleMoy);

		XMFLOAT3 posCamera = {
			RoundValue(m_placingModule.GetPosition().x, step),
			RoundValue(m_placingModule.GetPosition().y, step),
			RoundValue(m_placingModule.GetPosition().z, step)
		};

		XMFLOAT4 rotCamera = m_placingModule.GetRotation();
		XMFLOAT3 scaleCamera = m_placingModule.GetScale();
		uint32_t meshID = m_placingModule.GetMesh();
		uint32_t textureID = m_placingModule.GetTexture();

		std::string gmName = "GM" + std::to_string(m_newIdGM);

		CreateGameObject(gmName, meshID, textureID);
		GetGameObjectByName(gmName).SetPosition({ posCamera });
		GetGameObjectByName(gmName).SetRotation({ rotCamera });
		GetGameObjectByName(gmName).SetScale({ scaleCamera });

		GetGameObjectByName(gmName).SetTag(TAG_Object);

		std::string msg = "\nAdded " + gmName + " At[ X: " + RoundValueStr(GetGameObjectByName(gmName).GetPosition().x) + " Y: " + RoundValueStr(GetGameObjectByName(gmName).GetPosition().y) + " Z: " + RoundValueStr(GetGameObjectByName(gmName).GetPosition().z);
		OutputDebugStringA(msg.c_str());

		m_newIdGM++;
	}


	// Reset placing Module (cannot rotate after for some reason..)
	if (InputManager::GetKeyIsPressed(VK_F1))
	{
		m_placingModule.SetScale({ 1.f, 1.f, 1.f });
		m_placingModule.SetRotation({ 0.f, 0.f, 0.f, 1.f });
		m_placingModule.GetComponent<TransformComponent>()->dirty = true;
	}

	// Undo
	if (InputManager::GetKeyIsReleased(VK_F2))
	{
		if (!GetSceneGameObjects().empty())
		{
			if (GetSceneGameObjects().back().GetTag() == TAG_Object)
			{
				m_lastPlacedGmName = GetSceneGameObjects().back().GetName();
				m_lastPlacedGmPos = GetSceneGameObjects().back().GetPosition();

				DestroyGameObject(GetSceneGameObjects().back());
			}
		}
	}

	// Redo (Prototype)
	if (InputManager::GetKeyIsReleased(VK_F3))
	{
		if (m_lastPlacedGmName != "")
		{
			CreateGameObject(m_lastPlacedGmName);
			GetGameObjectByName(m_lastPlacedGmName).SetPosition(m_lastPlacedGmPos);
			GetGameObjectByName(m_lastPlacedGmName).SetTag(TAG_Object);

			m_lastPlacedGmName = "";
		}
	}

	// Generating scene outpout
	if (InputManager::GetKeyIsReleased(VK_RETURN))
	{
		OutputDebugStringA("\n\n----------- GENERATING SCENE CM's -----------");
		OutputDebugStringA("\n//COPY HERE");
		OutputDebugStringA("\n{");
		for (auto gm : GetSceneGameObjects())
		{
			if (gm.GetTag() == TAG_Object)
			{
				//auto& test = gm.GetPosition();
				//std::string cm_create = std::string("\nCreateGameObject(\"") + gm.GetName() + "\");";
				std::string cm_create = std::string("\nCreateGameObject(\"") + gm.GetName() + "\"" + "," + std::to_string(gm.GetMesh()) + "," + std::to_string(gm.GetTexture()) + ");";
				std::string cm_position = std::string("\nGetGameObjectByName(\"") + gm.GetName() + "\").SetPosition({ " + RoundValueStr(gm.GetPosition().x) + "," + RoundValueStr(gm.GetPosition().y) + "," + RoundValueStr(gm.GetPosition().z) + " });";
				std::string cm_rotation = std::string("\nGetGameObjectByName(\"") + gm.GetName() + "\").SetRotation({ " + RoundValueStr(gm.GetRotation().x) + "," + RoundValueStr(gm.GetRotation().y) + "," + RoundValueStr(gm.GetRotation().z) + "," + RoundValueStr(gm.GetRotation().w) + " });";
				std::string cm_scale = std::string("\nGetGameObjectByName(\"") + gm.GetName() + "\").SetScale({ " + RoundValueStr(gm.GetScale().x) + "," + RoundValueStr(gm.GetScale().y) + "," + RoundValueStr(gm.GetScale().z) + " });";

				OutputDebugStringA(cm_create.c_str());
				OutputDebugStringA(cm_position.c_str());
				OutputDebugStringA(cm_rotation.c_str());
				OutputDebugStringA(cm_scale.c_str());
			}
		}
		OutputDebugStringA("\n}");
		OutputDebugStringA("\n----------- --------------------- -----------\n");
	}

	// LockMouse
	if (InputManager::GetKeyIsReleased(VK_F5))
	{
		OutputDebugStringA("\LockMouse\n");
		if (InputManager::IsMouseLocked())
		{
			DisableLockCursor();
		}
		else
		{
			EnableLockCursor();
		}
	}

	if (InputManager::IsMouseLocked())
	{
		CenterLockCursor();
	}

	// Change type of gameobject (prototype)
	if (InputManager::GetKeyIsReleased('1'))
	{
		m_placingModule.SetTexture(0);
	}
	if (InputManager::GetKeyIsReleased('2'))
	{
		m_placingModule.SetTexture(1);
	}
	if (InputManager::GetKeyIsReleased('3'))
	{
		m_placingModule.SetTexture(2);
	}
}

void DevScene::Release()
{

}

void DevScene::CameraDevSystem(float deltatime)
{
	// 1) Debut/fin orbite
	SHORT state = GetAsyncKeyState(VK_RBUTTON);
	bool pressed = (state & 0x8000) != 0;
	if (pressed && !m_orbiting)
	{
		m_orbiting = true;
		SetCapture(m_hWnd);
		ShowCursor(FALSE);
		GetCursorPos(&m_lastMousePos);
	}
	else if (!pressed && m_orbiting)
	{
		m_orbiting = false;
		ReleaseCapture();
		ShowCursor(TRUE);
	}

	// 2) Si orbite active, lire dx/dy et ajuster yaw+pitch
	if (m_orbiting)
	{
		POINT cur; GetCursorPos(&cur);
		int dx = cur.x - m_lastMousePos.x;
		int dy = cur.y - m_lastMousePos.y;
		m_orbitYaw += dx * m_sensitivity;
		m_orbitPitch += -dy * m_sensitivity; // inverser si necessaire selon sens
		m_orbitPitch = std::clamp(m_orbitPitch, -89.0f, +89.0f);
		if (m_orbitYaw >= 360.0f) m_orbitYaw -= 360.0f;
		else if (m_orbitYaw < 0.0f) m_orbitYaw += 360.0f;
		SetCursorPos(m_lastMousePos.x, m_lastMousePos.y);
	}

	// 3) Recalcule de la position camera selon angle et radius, et oriente la camera vers le cube
	{
		// Centre de l’orbite = position du cube
		XMFLOAT3 center = m_placingModule.GetPosition();

		// 3.1) Calculer un radius dynamique en fonction de la taille du cube
		XMFLOAT3 scale = m_placingModule.GetScale();
		// Trouver le plus grand des trois composantes
		float maxScale = std::max(scale.x, std::max(scale.y, scale.z));
		// Rayon minimal et marge autour de l’objet
		float radiusMin = 3.0f;
		float radiusMargin = 1.5f;
		float dynamicRadius = std::max(radiusMin, maxScale * radiusMargin);

		// 3.2) Convertir yaw/pitch en radians
		float yawRad = XMConvertToRadians(m_orbitYaw);
		float pitchRad = XMConvertToRadians(m_orbitPitch);
		float cosP = cosf(pitchRad);

		// 3.3) Calculer la position sphérique
		XMFLOAT3 camPos;
		camPos.x = center.x + dynamicRadius * cosP * sinf(yawRad);
		camPos.y = center.y + dynamicRadius * sinf(pitchRad);
		camPos.z = center.z + dynamicRadius * cosP * cosf(yawRad);

		m_camera.SetPosition(camPos);
		if (auto tCam = m_camera.GetComponent<TransformComponent>()) tCam->dirty = true;

		// 3.4) Orienter la caméra pour qu’elle regarde le centre
		XMVECTOR eye = XMLoadFloat3(&camPos);
		XMVECTOR at = XMLoadFloat3(&center);
		XMVECTOR up = XMVectorSet(0, 1, 0, 0);
		XMMATRIX view = XMMatrixLookAtLH(eye, at, up);
		XMMATRIX camWorld = XMMatrixInverse(nullptr, view);
		XMVECTOR quat = XMQuaternionRotationMatrix(camWorld);
		XMFLOAT4 qf; XMStoreFloat4(&qf, quat);
		m_camera.SetRotation(qf);
		if (auto tCam2 = m_camera.GetComponent<TransformComponent>()) tCam2->dirty = true;
	}

	// 2. Deplacement relatif ala camera
	// Recuperer positions
	XMFLOAT3 camPosF = m_camera.GetPosition();
	XMFLOAT3 objPosF = m_placingModule.GetPosition();
	XMVECTOR camPos = XMLoadFloat3(&camPosF);
	XMVECTOR objPos = XMLoadFloat3(&objPosF);

	// Calculer forward et right ・partir de la rotation de la cam駻a
	XMFLOAT4 camQuatF = m_camera.GetRotation();
	XMVECTOR camQuat = XMLoadFloat4(&camQuatF);
	XMMATRIX camRotMat = XMMatrixRotationQuaternion(camQuat);
	// Avant local de la camera : +Z
	XMVECTOR forwardV = XMVector3Normalize(XMVector3TransformNormal(XMVectorSet(0, 0, 1, 0), camRotMat));
	// On ne veut que la composante horizontale pour avancer/reculer sur le sol :
	forwardV = XMVectorSetY(forwardV, 0.0f);
	if (!XMVector3Equal(forwardV, XMVectorZero()))
	{
		forwardV = XMVector3Normalize(forwardV);
	}

	// Right comme cross(up, forward)
	XMVECTOR upV = XMVectorSet(0, 1, 0, 0);
	XMVECTOR rightV = XMVector3Normalize(XMVector3Cross(upV, forwardV));

	// Construire moveV global
	XMVECTOR moveV = XMVectorZero();
	if (InputManager::GetKeyIsPressed('Z')) moveV += forwardV;
	if (InputManager::GetKeyIsPressed('S')) moveV -= forwardV;
	if (InputManager::GetKeyIsPressed('D')) moveV += rightV;
	if (InputManager::GetKeyIsPressed('Q')) moveV -= rightV;
	// Composante verticale
	if (InputManager::GetKeyIsPressed(VK_SPACE))   moveV += upV;
	if (InputManager::GetKeyIsPressed(VK_CONTROL)) moveV -= upV;

	// Appliquer shift/run
	float speed = InputManager::GetKeyIsPressed(VK_SHIFT) ? m_camRunSpeed : m_camWalkSpeed;

	// Si vecteur non nul, normaliser puis scale
	if (!XMVector3Equal(moveV, XMVectorZero())) {
		moveV = XMVector3Normalize(moveV);
		XMVECTOR offset = moveV * (speed * deltatime);
		XMVECTOR newPos = objPos + offset;
		XMFLOAT3 newPosF; XMStoreFloat3(&newPosF, newPos);
		m_placingModule.SetPosition(newPosF);
		if (auto t = m_placingModule.GetComponent<TransformComponent>())
		{
			t->dirty = true;
		}
	}
}

std::string DevScene::Float2Str(float value)
{
	char buf[32];
	std::snprintf(buf, sizeof(buf), "%.2f", value);
	return buf;
}
std::string DevScene::RoundValueStr(float value)
{
	return std::to_string(static_cast<int>(std::round(value)));
}
//float DevScene::RoundValue(float value)
//{
//	if (m_QuadrillageModeIsOn) 
//	{
//		return std::round(value);
//	}
//	else
//	{
//		return value;
//	}
//}
float DevScene::RoundValue(float value, int roundTo)
{
	if (m_QuadrillageModeIsOn && roundTo > 0)
		return std::round(value / roundTo) * roundTo;
	else
		return value;
}
int DevScene::ComputeGridStep(float scale)
{
	if (scale < 5.0f)      return 1;  // unité
	else if (scale < 50.0f) return 5;  // 5aine
	else                   return 10; // dizaine
}