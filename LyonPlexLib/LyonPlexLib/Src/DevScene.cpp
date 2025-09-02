#include "pch.h"
#include "DevScene.h"
#include "Boulder.h"

#undef max
#undef min
#include <algorithm>

XMFLOAT3 POSITION_BASE = { 325, -2, 50 };


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
	//CreateGameObject("Map");
	//GetGameObjectByName("Map").SetMesh(MESHES::MAP);
	//GetGameObjectByName("Map").SetPosition({ -10,0,0 });


	CreateGameObject("Grid", DimensionalType::TYPE_3D_TRANSPARENT, true);
	auto a = GetGameObjectByName("Grid");
	a.SetTexture(TEXTURES::ARMS);
	a.SetScale({ 20,1,20 });
	//a.GetComponent<MeshComponent>()->alpha = 0.2;

	CreateGameObject("Grid2", DimensionalType::TYPE_3D_TRANSPARENT, true);
	a = GetGameObjectByName("Grid2");
	a.SetTexture(TEXTURES::GRID);
	a.SetScale({ 20,0,20 });
	a.SetPosition({ 0,4,0 });
	a.GetComponent<MeshComponent>()->alpha = 0.5;

	m_newIdGM = 0;
	m_camWalkSpeed = 30.f;
	m_camRunSpeed = 60.f;
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
	// Camera
	CameraDevSystem(deltatime);

	if (InputManager::GetKeyIsJustPressed('P'))
	{
		if (m_placingModule.GetTexture() == UINT_MAX)
		{
			m_placingModule.SetTexture(TEXTURES::NOTEXTURE);
		}
		else
			m_placingModule.SetTexture(UINT_MAX); // texture d'objet 3D importe depuis logiciel 3D
	}
	static bool slow = false;
	if (InputManager::GetKeyIsJustPressed('X'))
	{
		slow = !slow;
	}
	// Movements
	if (InputManager::GetKeyIsPressed(VK_SHIFT))
	{
		m_camSpeed = m_camRunSpeed;
		m_scaleSpeed = 5;
		m_zoomSensitivity = 10;
	}
	else if (slow)
	{
		m_camSpeed = m_camWalkSpeed / 10;
		m_scaleSpeed = 0.1;
		m_zoomSensitivity = 0.1;
	}
	else
	{
		m_camSpeed = m_camWalkSpeed;
		m_scaleSpeed = 1;
		m_zoomSensitivity = 1;
	}

	// cam rotate(prototype)
	EnableMouseRotationFor(m_placingModule, 0.2f);

	// Change mode
	if (InputManager::GetKeyIsReleased('H'))
	{
		if (m_actualMode == EditMode::Build)
		{
			m_actualMode = EditMode::Hitbox;
			OutputDebugStringA("\Mode Hitbox : ON \n");

			// Creer la hitbox
			CreateGameObject("placingHitbox", DimensionalType::TYPE_3D_TRANSPARENT);
			m_placingHitbox = GetGameObjectByName("placingHitbox");
			m_placingHitbox.SetPosition(m_placingModule.GetPosition());
			m_placingHitbox.SetScale(m_placingModule.GetScale());
			m_placingHitbox.SetRotation(m_placingModule.GetRotation());
			m_placingHitbox.SetTexture(TEXTURES::stop);
			m_placingHitbox.GetComponent<MeshComponent>()->alpha = 0.4;
		}
		else
		{
			m_actualMode = EditMode::Build;
			OutputDebugStringA("\Mode Build : ON \n");
		}
	}

	if (m_actualMode == EditMode::Build)
	{
		// Rotate
		if (InputManager::GetKeyIsPressed(VK_RIGHT))
		{
			m_placingModule.GetComponent<TransformComponent>()->AddRotation(0.f, -1.f, 0.f);
			m_placingModule.GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed(VK_LEFT))
		{
			m_placingModule.GetComponent<TransformComponent>()->AddRotation(0.f, 1.f, 0.f);
			m_placingModule.GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed(VK_UP))
		{
			m_placingModule.GetComponent<TransformComponent>()->AddRotation(1.f, 0.f, 0.f);
			m_placingModule.GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed(VK_DOWN))
		{
			m_placingModule.GetComponent<TransformComponent>()->AddRotation(-1.f, 0.f, 0.f);
			m_placingModule.GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed('L'))
		{
			m_placingModule.GetComponent<TransformComponent>()->AddRotation(0.f, 0.f, 1.f);
			m_placingModule.GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed('M'))
		{
			m_placingModule.GetComponent<TransformComponent>()->AddRotation(0.f, 0.f, -1.f);
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



		//Mode cadriage
		if (InputManager::GetKeyIsReleased('W')) // Quadriage arronndi au 1, 5 ou 10 le + proche en fonction de la scale
		{
			m_QuadrillageModeIsOn = !m_QuadrillageModeIsOn;

			m_QuadrillageModeIsOn ? OutputDebugStringA("\Quadrillage : ON \n") : OutputDebugStringA("\Quadrillage : OFF \n");

		}
		//Mode cadriage round force a 1
		if (InputManager::GetKeyIsReleased('C')) // Force le quadrillage a arrondir a l'unite pres
		{
			m_QuadrillageUnitaireIsOn = !m_QuadrillageUnitaireIsOn;

			m_QuadrillageUnitaireIsOn ? OutputDebugStringA("\Quadrillage UNITAIRE : ON \n") : OutputDebugStringA("\Quadrillage UNITAIRE : OFF \n");

		}

		// Adding blocks (make a function in this scene)
		if (InputManager::GetKeyIsReleased(VK_LBUTTON))
		{
			auto& blocScale = m_placingModule.GetScale();
			float scaleMoy = 0;

			m_QuadrillageUnitaireIsOn ? scaleMoy = 1 : scaleMoy = (blocScale.x + blocScale.y + blocScale.z) / 3;


			int   step = ComputeGridStep(scaleMoy);

			XMFLOAT3 posCamera = {
				RoundValue(m_placingModule.GetPosition().x, step),
				RoundValue(m_placingModule.GetPosition().y, step),
				RoundValue(m_placingModule.GetPosition().z, step)
			};

			XMFLOAT4 rotCamera = m_placingModule.GetRotation();
			XMFLOAT3 scaleCamera = m_placingModule.GetScale();
			uint32_t meshID = m_placingModule.GetMeshID();
			uint32_t textureID = m_placingModule.GetTexture();

			std::string gmName = "Next " + std::to_string(m_newIdGM);

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
				if (GetSceneGameObjects().back().get()->GetTag() == TAG_Object)
				{
					m_lastPlacedGmName = GetSceneGameObjects().back().get()->GetName();
					m_lastPlacedGmPos = GetSceneGameObjects().back().get()->GetPosition();

					DestroyGameObject(*GetSceneGameObjects().back().get());
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
			for (auto& gameObj : GetSceneGameObjects())
			{
				auto* gm = gameObj.get();
				if (gm->GetTag() == TAG_Object)
				{
					//Creer les msg de sorties

					std::string cm_create;

					// Si on creer une hitbox seul ou non
					if (gm->GetTexture() != TEXTURES::stop)
					{
						cm_create = std::string("\nCreateGameObject(\"") + gm->GetName() + "\"" + "," + std::to_string(gm->GetMeshID()) + "," + std::to_string(gm->GetTexture()) + ");";
					}
					else
					{
						cm_create = std::string("\CreateGameHitbox(\"") + gm->GetName() + "\"" + ");";
						gm->SetColliderX(gm->GetComponent<TransformComponent>()->scale.x / 2);
						gm->SetColliderY(gm->GetComponent<TransformComponent>()->scale.y / 2);
						gm->SetColliderZ(gm->GetComponent<TransformComponent>()->scale.z / 2);
					}
					std::string cm_position = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\").SetPosition({ " + RoundValueStr(gm->GetPosition().x) + "," + RoundValueStr(gm->GetPosition().y) + "," + RoundValueStr(gm->GetPosition().z) + " });";
					std::string cm_rotation = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\").SetRotation({ " + FloatToStringNoTrailingZeros(gm->GetRotation().x) + "," + FloatToStringNoTrailingZeros(gm->GetRotation().y) + "," + FloatToStringNoTrailingZeros(gm->GetRotation().z) + "," + FloatToStringNoTrailingZeros(gm->GetRotation().w) + " });";
					std::string cm_scale = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\").SetScale({ " + RoundValueStr(gm->GetScale().x) + "," + RoundValueStr(gm->GetScale().y) + "," + RoundValueStr(gm->GetScale().z) + " });";
					std::string cm_collider = std::string("\nGetGameObjectByName(\"") + gm->GetName() 
						+ "\").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({" 
						+ FloatToStringNoTrailingZeros(gm->GetColliderX()) + ", " + FloatToStringNoTrailingZeros(gm->GetColliderY()) + ", " + FloatToStringNoTrailingZeros(gm->GetColliderZ()) + "}, {"
						+ FloatToStringNoTrailingZeros(gm->GetColliderOffSet().x) + ", " + FloatToStringNoTrailingZeros(gm->GetColliderOffSet().y) + ", " + FloatToStringNoTrailingZeros(gm->GetColliderOffSet().z)
						+ " })));";


					OutputDebugStringA(cm_create.c_str());
					OutputDebugStringA(cm_position.c_str());
					OutputDebugStringA(cm_rotation.c_str());
					OutputDebugStringA(cm_scale.c_str());
					if (gm->GetColliderX() > 0 || gm->GetTexture() == TEXTURES::stop) //dont forget to set colliderxyz with texture stop
					{
						OutputDebugStringA(cm_collider.c_str());
					}
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
			//m_placingModule.SetTexture(0);

			m_curMeshID -= 1;
			if (m_curMeshID < 0)
				m_curMeshID = MESHES::TotalMeshCount - 1;
			m_placingModule.SetMesh(m_curMeshID);
		}
		if (InputManager::GetKeyIsReleased('2'))
		{
			m_curMeshID += 1;
			if (m_curMeshID >= MESHES::TotalMeshCount)
				m_curMeshID = 0;
			m_placingModule.SetMesh(m_curMeshID);
		}

		// Change type of gameobject (prototype)
		if (InputManager::GetKeyIsReleased('3'))
		{
			//m_placingModule.SetTexture(0);

			m_curTexID -= 1;
			if (m_curTexID < 0)
				m_curTexID = TEXTURES::TotalTextureCount - 1;
			m_placingModule.SetTexture(m_curTexID);
		}
		if (InputManager::GetKeyIsReleased('4'))
		{
			m_curTexID += 1;
			if (m_curTexID >= TEXTURES::TotalTextureCount)
				m_curTexID = 0;
			m_placingModule.SetTexture(m_curTexID);
		}
	}
	if (m_actualMode == EditMode::Hitbox)
	{
		// Scale
		if (InputManager::GetKeyIsJustPressed(VK_ADD))
		{
			m_placingHitbox.GetComponent<TransformComponent>()->scale.x += m_scaleSpeed;
			m_placingHitbox.GetComponent<TransformComponent>()->scale.y += m_scaleSpeed;
			m_placingHitbox.GetComponent<TransformComponent>()->scale.z += m_scaleSpeed;
			m_placingHitbox.GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed(VK_SUBTRACT))
		{
			m_placingHitbox.GetComponent<TransformComponent>()->scale.x -= m_scaleSpeed;
			m_placingHitbox.GetComponent<TransformComponent>()->scale.y -= m_scaleSpeed;
			m_placingHitbox.GetComponent<TransformComponent>()->scale.z -= m_scaleSpeed;
			m_placingHitbox.GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('R'))
		{
			m_placingHitbox.GetComponent<TransformComponent>()->scale.x += m_scaleSpeed;
			m_placingHitbox.GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('T'))
		{
			m_placingHitbox.GetComponent<TransformComponent>()->scale.x -= m_scaleSpeed;
			m_placingHitbox.GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('Y'))
		{
			m_placingHitbox.GetComponent<TransformComponent>()->scale.y += m_scaleSpeed;
			m_placingHitbox.GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('U'))
		{
			m_placingHitbox.GetComponent<TransformComponent>()->scale.y -= m_scaleSpeed;
			m_placingHitbox.GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('I'))
		{
			m_placingHitbox.GetComponent<TransformComponent>()->scale.z += m_scaleSpeed;
			m_placingHitbox.GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('O'))
		{
			m_placingHitbox.GetComponent<TransformComponent>()->scale.z -= m_scaleSpeed;
			m_placingHitbox.GetComponent<TransformComponent>()->dirty = true;
		}

		if (InputManager::GetKeyIsJustPressed('Z'))
		{
			m_placingHitbox.GetComponent<TransformComponent>()->position.z += m_scaleSpeed / 10;
			m_placingHitbox.GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('S'))
		{
			m_placingHitbox.GetComponent<TransformComponent>()->position.z -= m_scaleSpeed / 10;
			m_placingHitbox.GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('Q'))
		{
			m_placingHitbox.GetComponent<TransformComponent>()->position.x += m_scaleSpeed / 10;
			m_placingHitbox.GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('D'))
		{
			m_placingHitbox.GetComponent<TransformComponent>()->position.x -= m_scaleSpeed / 10;
			m_placingHitbox.GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed(VK_SPACE))
		{
			m_placingHitbox.GetComponent<TransformComponent>()->position.y += m_scaleSpeed / 10;
			m_placingHitbox.GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed(VK_CONTROL))
		{
			m_placingHitbox.GetComponent<TransformComponent>()->position.y -= m_scaleSpeed / 10;
			m_placingHitbox.GetComponent<TransformComponent>()->dirty = true;
		}

		// Placing hitbox and block
		if (InputManager::GetKeyIsReleased(VK_LBUTTON))
		{
			auto& blocScale = m_placingModule.GetScale();
			float scaleMoy = 0;

			m_QuadrillageUnitaireIsOn ? scaleMoy = 1 : scaleMoy = (blocScale.x + blocScale.y + blocScale.z) / 3;


			int   step = ComputeGridStep(scaleMoy);

			XMFLOAT3 posCamera = {
				RoundValue(m_placingModule.GetPosition().x, step),
				RoundValue(m_placingModule.GetPosition().y, step),
				RoundValue(m_placingModule.GetPosition().z, step)
			};

			XMFLOAT4 rotCamera = m_placingModule.GetRotation();
			XMFLOAT3 scaleCamera = m_placingModule.GetScale();
			uint32_t meshID = m_placingModule.GetMeshID();
			uint32_t textureID = m_placingModule.GetTexture();

			std::string gmName = "Next " + std::to_string(m_newIdGM);

			CreateGameObject(gmName, meshID, textureID);
			auto& gameObj = GetGameObjectByName(gmName);
			gameObj.SetPosition({ posCamera });
			gameObj.SetRotation({ rotCamera });
			gameObj.SetScale({ scaleCamera });
			gameObj.SetTag(TAG_Object);

			// hitbox
			gameObj.SetColliderX(m_placingHitbox.GetComponent<TransformComponent>()->scale.x / 2);
			gameObj.SetColliderY(m_placingHitbox.GetComponent<TransformComponent>()->scale.y / 2);
			gameObj.SetColliderZ(m_placingHitbox.GetComponent<TransformComponent>()->scale.z / 2);
			XMFLOAT3 offset = 
			{ 
				m_placingHitbox.GetComponent<TransformComponent>()->position.x - m_placingModule.GetComponent<TransformComponent>()->position.x,
				m_placingHitbox.GetComponent<TransformComponent>()->position.y - m_placingModule.GetComponent<TransformComponent>()->position.y,
				m_placingHitbox.GetComponent<TransformComponent>()->position.z - m_placingModule.GetComponent<TransformComponent>()->position.z,
			};

			gameObj.SetColliderOffSet(offset);
			m_placingHitbox.SetPosition(gameObj.GetPosition());

			std::string msg = "\nAdded " + gmName + " At[ X: " + RoundValueStr(gameObj.GetPosition().x) + " Y: " + RoundValueStr(gameObj.GetPosition().y) + " Z: " + RoundValueStr(gameObj.GetPosition().z);
			OutputDebugStringA(msg.c_str());

			m_newIdGM++;
			m_actualMode = EditMode::Build;
		}
	}

	// ChangeScene
	if (InputManager::GetKeyIsReleased('A'))
	{
		//ChangeScene("MainMenuScene");
		ChangeScene("GameScene");
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
		//// Centre de l’orbite = position du cube
		//XMFLOAT3 center = m_placingModule.GetPosition();

		//// 3.1) Calculer un radius dynamique en fonction de la taille du cube
		//XMFLOAT3 scale = m_placingModule.GetScale();
		//// Trouver le plus grand des trois composantes
		////float maxScale = std::max(scale.x, std::max(scale.y, scale.z));
		//float scaleMoy = (scale.x + scale.y + scale.z) / 3;
		//// Rayon minimal et marge autour de l’objet
		//float radiusMin = 0.5f;
		//float radiusMargin = 0.00000055f;
		//float dynamicRadius = std::max(radiusMin, scaleMoy * radiusMargin);

		//// 3.2) Convertir yaw/pitch en radians
		//float yawRad = XMConvertToRadians(m_orbitYaw);
		//float pitchRad = XMConvertToRadians(m_orbitPitch);
		//float cosP = cosf(pitchRad);

		//// 3.3) Calculer la position sphérique
		//XMFLOAT3 camPos;
		//camPos.x = center.x + dynamicRadius * cosP * sinf(yawRad);
		//camPos.y = center.y + dynamicRadius * sinf(pitchRad);
		//camPos.z = center.z + dynamicRadius * cosP * cosf(yawRad);

		//m_camera.SetPosition(camPos);
			// 3.1) Calculer radius dynamique
		XMFLOAT3 scale = m_placingModule.GetScale();
		float maxScale = std::max({ scale.x, scale.y, scale.z });
		float radiusMin = 2.0f;
		float radiusMargin = 0.55f;
		float dynamicRadius = std::max(radiusMin, maxScale * radiusMargin);

		// 3.2) Intégrer zoom de la molette
		int wheelDelta = InputManager::GetAndResetWheelDelta();
		m_zoomOffset += (wheelDelta / 120.0f) * m_zoomSensitivity;
		m_zoomOffset = std::clamp(m_zoomOffset, m_zoomMin, m_zoomMax);
		float finalRadius = dynamicRadius + m_zoomOffset;
		finalRadius = std::max(radiusMin * 0.5f, finalRadius);

		// 3.3) Convertir angles et positionner caméra
		float yawRad = XMConvertToRadians(m_orbitYaw);
		float pitchRad = XMConvertToRadians(m_orbitPitch);
		float cosP = cosf(pitchRad);
		XMFLOAT3 center = m_placingModule.GetPosition();

		XMFLOAT3 camPosTemp;
		camPosTemp.x = center.x + finalRadius * cosP * sinf(yawRad);
		camPosTemp.y = center.y + finalRadius * sinf(pitchRad);
		camPosTemp.z = center.z + finalRadius * cosP * cosf(yawRad);

		m_camera.SetPosition(camPosTemp);
		if (auto tCam = m_camera.GetComponent<TransformComponent>()) tCam->dirty = true;

		// 3.4) Orienter la caméra pour qu’elle regarde le centre
		XMVECTOR eye = XMLoadFloat3(&camPosTemp);
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
	if (m_actualMode == EditMode::Build)
	{
		if (InputManager::GetKeyIsPressed('Z')) moveV += forwardV;
		if (InputManager::GetKeyIsPressed('S')) moveV -= forwardV;
		if (InputManager::GetKeyIsPressed('D')) moveV += rightV;
		if (InputManager::GetKeyIsPressed('Q')) moveV -= rightV;
		// Composante verticale
		if (InputManager::GetKeyIsPressed(VK_SPACE))   moveV += upV;
		if (InputManager::GetKeyIsPressed(VK_CONTROL)) moveV -= upV;
	}


	// Appliquer shift/run
	//float speed = InputManager::GetKeyIsPressed(VK_SHIFT) ? m_camRunSpeed : m_camWalkSpeed;
	float speed = m_camSpeed;

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
std::string DevScene::FloatToStringNoTrailingZeros(float value)
{
	std::ostringstream oss;
	oss << std::fixed
		// max_digits10 garantit qu'on ne « coupe » aucune décimale significative
		<< std::setprecision(std::numeric_limits<float>::max_digits10)
		<< value;
	std::string s = oss.str();
	// on vire les '0' superflus
	s.erase(s.find_last_not_of('0') + 1);
	// s'il reste un '.', on l'enlève aussi
	if (!s.empty() && s.back() == '.')
		s.pop_back();
	return s;
}