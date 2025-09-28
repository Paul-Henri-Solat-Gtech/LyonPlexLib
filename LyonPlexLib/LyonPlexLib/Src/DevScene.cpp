#include "pch.h"
#include "DevScene.h"
#include "Boulder.h"
#include "AdditionnalSceneObjects.h"


#undef max
#undef min
#include <algorithm>

XMFLOAT3 POSITION_BASE = { 325, -2, 50 };


void DevScene::Start()
{
	m_hWnd = mp_sceneManager->GetWindow();

	// Creer le cube (placingModule)
	CreateGameObject("placingModule");
	m_placingModule = FindGameObjectByName("placingModule");
	m_placingModule->SetPosition({ 0, 0, 0 }); // par exemple au centre
	m_placingModule->SetTexture(TEXTURES::NOTEXTURE);

	// Creer la camera
	CreateGameObject("camera", TYPE_3D, false);
	m_camera = FindGameObjectByName("camera");
	m_camera->AddComponent<CameraComponent>(new CameraComponent());

	XMFLOAT3 cubePos = m_placingModule->GetPosition();
	XMFLOAT3 camPos = m_camera->GetPosition();
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

	//CreateEntity("Light");
	//AddComponent<Type_3D>("Light", new Type_3D());
	//AddComponent<MeshComponent>("Light", new MeshComponent(MESHES::LOCAL_CUBE, TEXTURES::BOIS));
	//GetComponent<TransformComponent>("Light")->position = { 150,200, 200 };
	//AddComponent<LightComponent>("Light", new LightComponent(1));
	//GetComponent<LightComponent>("Light")->color = { 1,1,0.5 };
	//GetComponent<LightComponent>("Light")->direction = { 0, 0, 0 };
	//GetComponent<LightComponent>("Light")->range = 1000;

	CreateGameObject("Light");
	auto* a = FindGameObjectByName("Light");

	a->AddComponent<Type_3D>(new Type_3D());
	a->AddComponent<MeshComponent>(new MeshComponent(MESHES::LOCAL_CUBE, TEXTURES::BOIS));
	a->GetComponent<TransformComponent>()->position = { 150,200, 200 };
	a->AddComponent<LightComponent>(new LightComponent(1));
	a->GetComponent<LightComponent>()->color = { 1,1,0.5 };
	a->GetComponent<LightComponent>()->direction = { 0, 0, 0 };
	a->GetComponent<LightComponent>()->range = 1000;

	AdditionnalSceneObjects::CreateFirstObjects(this);

	CreateGameObject("BigOLIVE", 32, 4294967295);
	FindGameObjectByName("BigOLIVE")->SetPosition({ -13.425217628,27.63675499,-20.910137177 });
	FindGameObjectByName("BigOLIVE")->SetRotation({ 0,-0.725374341,0,0.688354611 });
	FindGameObjectByName("BigOLIVE")->SetScale({ 8,8,8 });
	CreateGameObject("SmallOLIVE", 32, 4294967295);
	FindGameObjectByName("SmallOLIVE")->SetPosition({ 72.241355896,13.902094841,148.184280396 });
	FindGameObjectByName("SmallOLIVE")->SetRotation({ 0,-0.061048683,0,0.998134851 });
	FindGameObjectByName("SmallOLIVE")->SetScale({ 4,4,4 });


	CreateGameObject("skybox", 2, 0);
	FindGameObjectByName("skybox")->SetPosition({ 0,0,0 });
	FindGameObjectByName("skybox")->SetRotation({ 0,0,0,1 });
	FindGameObjectByName("skybox")->SetScale({ -1000,-1000,-1000 });
	FindGameObjectByName("skybox")->SetMesh(MESHES::LOCAL_SPHERE);
	FindGameObjectByName("skybox")->SetTexture(TEXTURES::SKYBOX);

	// TEST TOUS LES MESHS
	//int i = MESHES::Temple;
	//float j = 0;
	//for (; i < MESHES::TotalMeshCount; i++)
	//{
	//	auto b = CreateGameObject("", i);
	//	 //= FindGameObjectByName("");
	//	b->SetScale({ 10,10,10 });
	//	b->SetPosition({ -150 + 50.f * j,0,0 });
	//	j++;
	//}


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

}

void DevScene::Update(float deltatime)
{


	static bool init2 = false;
	if (!init2)
	{
		static bool weedsCreated = false;
		CreateAdditionalHitboxes();
		AdditionnalSceneObjects::CreateWeeds(this);
		if (weedsCreated)
		{
			AdditionnalSceneObjects::CreateObjects(this);
			AdditionnalSceneObjects::CreateGrass(this);
			init2 = true;
		}
		weedsCreated = true;
	}

	// Camera
	CameraDevSystem(deltatime);

	if (InputManager::GetKeyIsJustPressed('P'))
	{
		if (m_placingModule->GetTexture() == UINT_MAX)
		{
			m_placingModule->SetTexture(TEXTURES::NOTEXTURE);
		}
		else
			m_placingModule->SetTexture(UINT_MAX); // texture d'objet 3D importe depuis logiciel 3D
	}
	static bool slow = false;
	if (InputManager::GetKeyIsJustPressed('X'))
	{
		slow = !slow;
	}
	// Movements
	if (InputManager::GetKeyIsPressed(VK_SHIFT))
	{
		//m_camSpeed = m_camRunSpeed;
		m_camSpeed = m_camWalkSpeed * 1.5;
		m_scaleSpeed = 5;
		m_zoomSensitivity = 10;
	}
	else if (slow)
	{
		m_camSpeed = m_camWalkSpeed / 4;
		m_scaleSpeed = 0.1;
		m_zoomSensitivity = 0.1;
		m_sensitivity = 0.015;
	}
	else
	{
		m_camSpeed = m_camWalkSpeed / 2;
		m_scaleSpeed = 1;
		m_zoomSensitivity = 1;
		m_sensitivity = 0.03;
	}

	// cam rotate(prototype)
	EnableMouseRotationFor(*m_placingModule, 0.2f);

	// Change mode
	if (InputManager::GetKeyIsReleased('H'))
	{
		if (m_actualMode == EditMode::Build)
		{
			m_actualMode = EditMode::Hitbox;
			OutputDebugStringA("\Mode Hitbox : ON \n");

			// Creer la hitbox
			CreateGameObject("placingHitbox", DimensionalType::TYPE_3D_TRANSPARENT);
			m_placingHitbox = FindGameObjectByName("placingHitbox");
			m_placingHitbox->SetPosition(m_placingModule->GetPosition());
			m_placingHitbox->SetScale(m_placingModule->GetScale());
			m_placingHitbox->SetRotation(m_placingModule->GetRotation());
			m_placingHitbox->SetTexture(TEXTURES::stop);
			m_placingHitbox->GetComponent<MeshComponent>()->alpha = 0.4;
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
			m_placingModule->GetComponent<TransformComponent>()->AddRotation(0.f, -1.f, 0.f);
			m_placingModule->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed(VK_LEFT))
		{
			m_placingModule->GetComponent<TransformComponent>()->AddRotation(0.f, 1.f, 0.f);
			m_placingModule->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed(VK_UP))
		{
			m_placingModule->GetComponent<TransformComponent>()->AddRotation(1.f, 0.f, 0.f);
			m_placingModule->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed(VK_DOWN))
		{
			m_placingModule->GetComponent<TransformComponent>()->AddRotation(-1.f, 0.f, 0.f);
			m_placingModule->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed('L'))
		{
			m_placingModule->GetComponent<TransformComponent>()->AddRotation(0.f, 0.f, 1.f);
			m_placingModule->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsPressed('M'))
		{
			m_placingModule->GetComponent<TransformComponent>()->AddRotation(0.f, 0.f, -1.f);
			m_placingModule->GetComponent<TransformComponent>()->dirty = true;
		}

		// Scale
		if (InputManager::GetKeyIsJustPressed(VK_ADD))
		{
			m_placingModule->GetComponent<TransformComponent>()->scale.x += m_scaleSpeed;
			m_placingModule->GetComponent<TransformComponent>()->scale.y += m_scaleSpeed;
			m_placingModule->GetComponent<TransformComponent>()->scale.z += m_scaleSpeed;
			m_placingModule->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed(VK_SUBTRACT))
		{
			m_placingModule->GetComponent<TransformComponent>()->scale.x -= m_scaleSpeed;
			m_placingModule->GetComponent<TransformComponent>()->scale.y -= m_scaleSpeed;
			m_placingModule->GetComponent<TransformComponent>()->scale.z -= m_scaleSpeed;
			m_placingModule->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('R'))
		{
			m_placingModule->GetComponent<TransformComponent>()->scale.x += m_scaleSpeed;
			m_placingModule->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('T'))
		{
			m_placingModule->GetComponent<TransformComponent>()->scale.x -= m_scaleSpeed;
			m_placingModule->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('Y'))
		{
			m_placingModule->GetComponent<TransformComponent>()->scale.y += m_scaleSpeed;
			m_placingModule->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('U'))
		{
			m_placingModule->GetComponent<TransformComponent>()->scale.y -= m_scaleSpeed;
			m_placingModule->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('I'))
		{
			m_placingModule->GetComponent<TransformComponent>()->scale.z += m_scaleSpeed;
			m_placingModule->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('O'))
		{
			m_placingModule->GetComponent<TransformComponent>()->scale.z -= m_scaleSpeed;
			m_placingModule->GetComponent<TransformComponent>()->dirty = true;
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
			auto& blocScale = m_placingModule->GetScale();
			float scaleMoy = 0;

			m_QuadrillageUnitaireIsOn ? scaleMoy = 1 : scaleMoy = (blocScale.x + blocScale.y + blocScale.z) / 3;


			int   step = ComputeGridStep(scaleMoy);

			XMFLOAT3 posCamera = {
				RoundValue(m_placingModule->GetPosition().x, step),
				RoundValue(m_placingModule->GetPosition().y, step),
				RoundValue(m_placingModule->GetPosition().z, step)
			};

			XMFLOAT4 rotCamera = m_placingModule->GetRotation();
			XMFLOAT3 scaleCamera = m_placingModule->GetScale();
			uint32_t meshID = m_placingModule->GetMeshID();
			uint32_t textureID = m_placingModule->GetTexture();

			std::string gmName = "Next " + std::to_string(m_newIdGM);

			CreateGameObject(gmName, meshID, textureID);
			FindGameObjectByName(gmName)->SetPosition({ posCamera });
			FindGameObjectByName(gmName)->SetRotation({ rotCamera });
			FindGameObjectByName(gmName)->SetScale({ scaleCamera });

			FindGameObjectByName(gmName)->SetTag(TAG_Object);

			std::string msg = "\nAdded " + gmName + " At[ X: " + RoundValueStr(FindGameObjectByName(gmName)->GetPosition().x) + " Y: " + RoundValueStr(FindGameObjectByName(gmName)->GetPosition().y) + " Z: " + RoundValueStr(FindGameObjectByName(gmName)->GetPosition().z);
			OutputDebugStringA(msg.c_str());

			m_newIdGM++;
		}


		// Reset placing Module (cannot rotate after for some reason..)
		if (InputManager::GetKeyIsPressed(VK_F1))
		{
			m_placingModule->SetScale({ 1.f, 1.f, 1.f });
			m_placingModule->SetRotation({ 0.f, 0.f, 0.f, 1.f });
			m_placingModule->GetComponent<TransformComponent>()->dirty = true;
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
				FindGameObjectByName(m_lastPlacedGmName)->SetPosition(m_lastPlacedGmPos);
				FindGameObjectByName(m_lastPlacedGmName)->SetTag(TAG_Object);

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
					if (gm->GetTexture() != TEXTURES::TEMPLE)
					{
						cm_create = std::string("\nCreateGameObject(\"") + gm->GetName() + "\"" + "," + std::to_string(gm->GetMeshID()) + "," + std::to_string(gm->GetTexture()) + ");";
					}
					else
					{
						cm_create = std::string("\nCreateGameHitbox(\"") + gm->GetName() + "\"" + ");";
						gm->SetColliderX(gm->GetComponent<TransformComponent>()->scale.x / 2);
						gm->SetColliderY(gm->GetComponent<TransformComponent>()->scale.y / 2);
						gm->SetColliderZ(gm->GetComponent<TransformComponent>()->scale.z / 2);
					}
					//std::string cm_position = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\")->SetPosition({ " + RoundValueStr(gm->GetPosition().x) + "," + RoundValueStr(gm->GetPosition().y) + "," + RoundValueStr(gm->GetPosition().z) + " });";
					std::string cm_position = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\")->SetPosition({ " + FloatToStringNoTrailingZeros(gm->GetPosition().x) + "," + FloatToStringNoTrailingZeros(gm->GetPosition().y) + "," + FloatToStringNoTrailingZeros(gm->GetPosition().z) + " });";
					std::string cm_rotation = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\")->SetRotation({ " + FloatToStringNoTrailingZeros(gm->GetRotation().x) + "," + FloatToStringNoTrailingZeros(gm->GetRotation().y) + "," + FloatToStringNoTrailingZeros(gm->GetRotation().z) + "," + FloatToStringNoTrailingZeros(gm->GetRotation().w) + " });";
					//std::string cm_scale = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\")->SetScale({ " + RoundValueStr(gm->GetScale().x) + "," + RoundValueStr(gm->GetScale().y) + "," + RoundValueStr(gm->GetScale().z) + " });";
					std::string cm_scale = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\")->SetScale({ " + FloatToStringNoTrailingZeros(gm->GetScale().x) + "," + FloatToStringNoTrailingZeros(gm->GetScale().y) + "," + FloatToStringNoTrailingZeros(gm->GetScale().z) + " });";
					std::string cm_collider = std::string("\nGetGameObjectByName(\"") + gm->GetName()
						+ "\")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ "
						+ FloatToStringNoTrailingZeros(gm->GetColliderX()) + ", " + FloatToStringNoTrailingZeros(gm->GetColliderY()) + ", " + FloatToStringNoTrailingZeros(gm->GetColliderZ())
						+ "}, { 0, 0, 0, 1}, {"
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
			//m_placingModule->SetTexture(0);

			m_curMeshID -= 1;
			if (m_curMeshID < 0)
				m_curMeshID = MESHES::TotalMeshCount - 1;
			if (m_curMeshID >= MESHES::TEMPLE)
				m_curTexID = UINT_MAX;
			else
				m_curTexID = TEXTURES::NOTEXTURE;
			m_placingModule->SetTexture(m_curTexID);
			m_placingModule->SetMesh(m_curMeshID);
		}
		if (InputManager::GetKeyIsReleased('2'))
		{
			m_curMeshID += 1;
			if (m_curMeshID >= MESHES::TotalMeshCount)
				m_curMeshID = 0;
			if (m_curMeshID >= MESHES::TEMPLE)
				m_curTexID = UINT_MAX;
			else
				m_curTexID = TEXTURES::NOTEXTURE;
			m_placingModule->SetTexture(m_curTexID);
			m_placingModule->SetMesh(m_curMeshID);
		}

		// Change type of gameobject (prototype)
		if (InputManager::GetKeyIsReleased('3'))
		{
			//m_placingModule->SetTexture(0);

			m_curTexID -= 1;
			if (m_curTexID < 0)
				m_curTexID = TEXTURES::TotalTextureCount - 1;
			m_placingModule->SetTexture(m_curTexID);
		}
		if (InputManager::GetKeyIsReleased('4'))
		{
			m_curTexID += 1;
			if (m_curTexID >= TEXTURES::TotalTextureCount)
				m_curTexID = 0;
			m_placingModule->SetTexture(m_curTexID);
		}
	}
	if (m_actualMode == EditMode::Hitbox)
	{
		// Scale
		if (InputManager::GetKeyIsJustPressed(VK_ADD))
		{
			m_placingHitbox->GetComponent<TransformComponent>()->scale.x += m_scaleSpeed;
			m_placingHitbox->GetComponent<TransformComponent>()->scale.y += m_scaleSpeed;
			m_placingHitbox->GetComponent<TransformComponent>()->scale.z += m_scaleSpeed;
			m_placingHitbox->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed(VK_SUBTRACT))
		{
			m_placingHitbox->GetComponent<TransformComponent>()->scale.x -= m_scaleSpeed;
			m_placingHitbox->GetComponent<TransformComponent>()->scale.y -= m_scaleSpeed;
			m_placingHitbox->GetComponent<TransformComponent>()->scale.z -= m_scaleSpeed;
			m_placingHitbox->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('R'))
		{
			m_placingHitbox->GetComponent<TransformComponent>()->scale.x += m_scaleSpeed;
			m_placingHitbox->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('T'))
		{
			m_placingHitbox->GetComponent<TransformComponent>()->scale.x -= m_scaleSpeed;
			m_placingHitbox->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('Y'))
		{
			m_placingHitbox->GetComponent<TransformComponent>()->scale.y += m_scaleSpeed;
			m_placingHitbox->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('U'))
		{
			m_placingHitbox->GetComponent<TransformComponent>()->scale.y -= m_scaleSpeed;
			m_placingHitbox->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('I'))
		{
			m_placingHitbox->GetComponent<TransformComponent>()->scale.z += m_scaleSpeed;
			m_placingHitbox->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('O'))
		{
			m_placingHitbox->GetComponent<TransformComponent>()->scale.z -= m_scaleSpeed;
			m_placingHitbox->GetComponent<TransformComponent>()->dirty = true;
		}

		if (InputManager::GetKeyIsJustPressed('Z'))
		{
			m_placingHitbox->GetComponent<TransformComponent>()->position.z += m_scaleSpeed / 10;
			m_placingHitbox->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('S'))
		{
			m_placingHitbox->GetComponent<TransformComponent>()->position.z -= m_scaleSpeed / 10;
			m_placingHitbox->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('Q'))
		{
			m_placingHitbox->GetComponent<TransformComponent>()->position.x += m_scaleSpeed / 10;
			m_placingHitbox->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed('D'))
		{
			m_placingHitbox->GetComponent<TransformComponent>()->position.x -= m_scaleSpeed / 10;
			m_placingHitbox->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed(VK_SPACE))
		{
			m_placingHitbox->GetComponent<TransformComponent>()->position.y += m_scaleSpeed / 10;
			m_placingHitbox->GetComponent<TransformComponent>()->dirty = true;
		}
		if (InputManager::GetKeyIsJustPressed(VK_CONTROL))
		{
			m_placingHitbox->GetComponent<TransformComponent>()->position.y -= m_scaleSpeed / 10;
			m_placingHitbox->GetComponent<TransformComponent>()->dirty = true;
		}

		// Placing hitbox and block
		if (InputManager::GetKeyIsReleased(VK_LBUTTON))
		{
			auto& blocScale = m_placingModule->GetScale();
			float scaleMoy = 0;

			m_QuadrillageUnitaireIsOn ? scaleMoy = 1 : scaleMoy = (blocScale.x + blocScale.y + blocScale.z) / 3;


			int   step = ComputeGridStep(scaleMoy);

			XMFLOAT3 posCamera = {
				RoundValue(m_placingModule->GetPosition().x, step),
				RoundValue(m_placingModule->GetPosition().y, step),
				RoundValue(m_placingModule->GetPosition().z, step)
			};

			XMFLOAT4 rotCamera = m_placingModule->GetRotation();
			XMFLOAT3 scaleCamera = m_placingModule->GetScale();
			uint32_t meshID = m_placingModule->GetMeshID();
			uint32_t textureID = m_placingModule->GetTexture();

			std::string gmName = "Next " + std::to_string(m_newIdGM);

			CreateGameObject(gmName, meshID, textureID);
			auto* gameObj = FindGameObjectByName(gmName);
			gameObj->SetPosition({ posCamera });
			gameObj->SetRotation({ rotCamera });
			gameObj->SetScale({ scaleCamera });
			gameObj->SetTag(TAG_Object);

			// hitbox
			gameObj->SetColliderX(m_placingHitbox->GetComponent<TransformComponent>()->scale.x / 2);
			gameObj->SetColliderY(m_placingHitbox->GetComponent<TransformComponent>()->scale.y / 2);
			gameObj->SetColliderZ(m_placingHitbox->GetComponent<TransformComponent>()->scale.z / 2);
			XMFLOAT3 offset =
			{
				m_placingHitbox->GetComponent<TransformComponent>()->position.x - m_placingModule->GetComponent<TransformComponent>()->position.x,
				m_placingHitbox->GetComponent<TransformComponent>()->position.y - m_placingModule->GetComponent<TransformComponent>()->position.y,
				m_placingHitbox->GetComponent<TransformComponent>()->position.z - m_placingModule->GetComponent<TransformComponent>()->position.z,
			};

			gameObj->SetColliderOffSet(offset);
			m_placingHitbox->SetPosition(gameObj->GetPosition());

			std::string msg = "\nAdded " + gmName + " At[ X: " + RoundValueStr(gameObj->GetPosition().x) + " Y: " + RoundValueStr(gameObj->GetPosition().y) + " Z: " + RoundValueStr(gameObj->GetPosition().z);
			OutputDebugStringA(msg.c_str());

			m_newIdGM++;
			m_actualMode = EditMode::Build;
		}
	}

	// ChangeScene
	if (InputManager::GetKeyIsReleased('N'))
	{
		ChangeScene("MainMenuScene");
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
		m_orbitPitch += /*-*/dy * m_sensitivity; // inverser si necessaire selon sens
		m_orbitPitch = std::clamp(m_orbitPitch, -89.0f, +89.0f);
		if (m_orbitYaw >= 360.0f) m_orbitYaw -= 360.0f;
		else if (m_orbitYaw < 0.0f) m_orbitYaw += 360.0f;
		SetCursorPos(m_lastMousePos.x, m_lastMousePos.y);
	}

	// 3) Recalcule de la position camera selon angle et radius, et oriente la camera vers le cube
	{
		//// Centre de l’orbite = position du cube
		//XMFLOAT3 center = m_placingModule->GetPosition();

		//// 3.1) Calculer un radius dynamique en fonction de la taille du cube
		//XMFLOAT3 scale = m_placingModule->GetScale();
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

		//m_camera->SetPosition(camPos);
			// 3.1) Calculer radius dynamique
		XMFLOAT3 scale = m_placingModule->GetScale();
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
		XMFLOAT3 center = m_placingModule->GetPosition();

		XMFLOAT3 camPosTemp;
		camPosTemp.x = center.x + finalRadius * cosP * sinf(yawRad);
		camPosTemp.y = center.y + finalRadius * sinf(pitchRad);
		camPosTemp.z = center.z + finalRadius * cosP * cosf(yawRad);

		m_camera->SetPosition(camPosTemp);
		if (auto tCam = m_camera->GetComponent<TransformComponent>()) tCam->dirty = true;

		// 3.4) Orienter la caméra pour qu’elle regarde le centre
		XMVECTOR eye = XMLoadFloat3(&camPosTemp);
		XMVECTOR at = XMLoadFloat3(&center);
		XMVECTOR up = XMVectorSet(0, 1, 0, 0);
		XMMATRIX view = XMMatrixLookAtLH(eye, at, up);
		XMMATRIX camWorld = XMMatrixInverse(nullptr, view);
		XMVECTOR quat = XMQuaternionRotationMatrix(camWorld);
		XMFLOAT4 qf; XMStoreFloat4(&qf, quat);
		m_camera->SetRotation(qf);
		if (auto tCam2 = m_camera->GetComponent<TransformComponent>()) tCam2->dirty = true;
	}



	// 2. Deplacement relatif ala camera
	// Recuperer positions
	XMFLOAT3 camPosF = m_camera->GetPosition();
	XMFLOAT3 objPosF = m_placingModule->GetPosition();
	XMVECTOR camPos = XMLoadFloat3(&camPosF);
	XMVECTOR objPos = XMLoadFloat3(&objPosF);

	// Calculer forward et right ・partir de la rotation de la cam駻a
	XMFLOAT4 camQuatF = m_camera->GetRotation();
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
		m_placingModule->SetPosition(newPosF);
		if (auto t = m_placingModule->GetComponent<TransformComponent>())
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


void DevScene::CreateAdditionalHitboxes()
{
	//CreateGameObject("temple_roof 0", 2, 1);
	//FindGameObjectByName("temple_roof 0")->SetPosition({ -194.986602783,28.808864594,22.194124222 });
	//FindGameObjectByName("temple_roof 0")->SetRotation({ 0,0,0,1 });
	//FindGameObjectByName("temple_roof 0")->SetScale({ 63,1,66 });

	CreateGameObject("tmplRoof", 40, 4294967295);
	FindGameObjectByName("tmplRoof")->SetPosition({ -195.431732178,29.433662415,22.693534851 });
	FindGameObjectByName("tmplRoof")->SetRotation({ 0,0,-0.707106948,-0.70710659 });
	FindGameObjectByName("tmplRoof")->SetScale({ 1,8.200000763,10 });


	CreateGameObject("HB_river 1", 18, 4294967295);
	FindGameObjectByName("HB_river 1")->SetPosition({ -34.95501709,16.350923538,-54.669914246 });
	FindGameObjectByName("HB_river 1")->SetRotation({ 0.811642468,0.145729944,0.56517303,-0.024059594 });
	FindGameObjectByName("HB_river 1")->SetScale({ 31,31,31 });
	CreateGameHitbox("HB_river 2");
	FindGameObjectByName("HB_river 2")->SetPosition({ 60.9427948,-12.511620522,76.680343628 });
	FindGameObjectByName("HB_river 2")->SetRotation({ 0,0,0,1 });
	FindGameObjectByName("HB_river 2")->SetScale({ 11,16,71 });
	FindGameObjectByName("HB_river 2")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 5.5, 8, 35.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_river 3");
	FindGameObjectByName("HB_river 3")->SetPosition({ 84.559341431,5.140720844,102.755966187 });
	FindGameObjectByName("HB_river 3")->SetRotation({ 0,-0.069756366,0,0.997564077 });
	FindGameObjectByName("HB_river 3")->SetScale({ 16,6,35 });
	FindGameObjectByName("HB_river 3")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8, 3, 17.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_river 4");
	FindGameObjectByName("HB_river 4")->SetPosition({ 80.821975708,1.298995256,74.564743042 });
	FindGameObjectByName("HB_river 4")->SetRotation({ 0,0,0,1 });
	FindGameObjectByName("HB_river 4")->SetScale({ 8,6,11 });
	FindGameObjectByName("HB_river 4")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 4, 3, 5.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_river 5");
	FindGameObjectByName("HB_river 5")->SetPosition({ 79.104804993,3.322609186,88.609771729 });
	FindGameObjectByName("HB_river 5")->SetRotation({ 0,0,0,1 });
	FindGameObjectByName("HB_river 5")->SetScale({ 8,6,11 });
	FindGameObjectByName("HB_river 5")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 4, 3, 5.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_river 6");
	FindGameObjectByName("HB_river 6")->SetPosition({ 80.986129761,2.754032373,48.787479401 });
	FindGameObjectByName("HB_river 6")->SetRotation({ 0,0,0,1 });
	FindGameObjectByName("HB_river 6")->SetScale({ 8,6,24 });
	FindGameObjectByName("HB_river 6")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 4, 3, 12 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_river 7");
	FindGameObjectByName("HB_river 7")->SetPosition({ 136.178527832,3.550265312,118.101867676 });
	FindGameObjectByName("HB_river 7")->SetRotation({ -0.0958312,0.01737209,-0.001672735,0.995244622 });
	FindGameObjectByName("HB_river 7")->SetScale({ 8,6,15 });
	FindGameObjectByName("HB_river 7")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 4, 3, 7.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_river 8");
	FindGameObjectByName("HB_river 8")->SetPosition({ 137.866577148,3.550265312,71.940162659 });
	FindGameObjectByName("HB_river 8")->SetRotation({ 0.130506247,0.016550573,-0.005537736,0.991293907 });
	FindGameObjectByName("HB_river 8")->SetScale({ 8,6,15 });
	FindGameObjectByName("HB_river 8")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 4, 3, 7.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_river 9");
	FindGameObjectByName("HB_river 9")->SetPosition({ 176.71635437,0.160697043,91.841545105 });
	FindGameObjectByName("HB_river 9")->SetRotation({ -0.156410724,0.017441837,-0.000609071,0.98753792 });
	FindGameObjectByName("HB_river 9")->SetScale({ 8,3,15 });
	FindGameObjectByName("HB_river 9")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 4, 1.5, 7.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_river 10");
	FindGameObjectByName("HB_river 10")->SetPosition({ 242.678619385,5.314517975,49.611206055 });
	FindGameObjectByName("HB_river 10")->SetRotation({ 0,0.165047616,0,0.986285627 });
	FindGameObjectByName("HB_river 10")->SetScale({ 21,6,6 });
	FindGameObjectByName("HB_river 10")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 10.5, 3, 3 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_river 11");
	FindGameObjectByName("HB_river 11")->SetPosition({ 304.746612549,5.422195435,84.00151825 });
	FindGameObjectByName("HB_river 11")->SetRotation({ 0,0.42261827,0,0.906307817 });
	FindGameObjectByName("HB_river 11")->SetScale({ 6,6,9 });
	FindGameObjectByName("HB_river 11")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 3, 3, 4.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_river 12");
	FindGameObjectByName("HB_river 12")->SetPosition({ 282.661987305,8.460522652,93.65511322 });
	FindGameObjectByName("HB_river 12")->SetRotation({ 0,0.25037998,0,0.968147695 });
	FindGameObjectByName("HB_river 12")->SetScale({ 10,16,14 });
	FindGameObjectByName("HB_river 12")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 5, 8, 7 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_river 13");
	FindGameObjectByName("HB_river 13")->SetPosition({ 289.54107666,1.974067688,103.994506836 });
	FindGameObjectByName("HB_river 13")->SetRotation({ 0.11150226,0.461130142,-0.087107465,0.875978649 });
	FindGameObjectByName("HB_river 13")->SetScale({ 11,5,11 });
	FindGameObjectByName("HB_river 13")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 5.5, 2.5, 5.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));

	CreateGameHitbox("HB_riverbed 2");
	FindGameObjectByName("HB_riverbed 2")->SetPosition({ -57.814807892,-25.027957916,34.836444855 });
	FindGameObjectByName("HB_riverbed 2")->SetRotation({ 0,0,-0.113203213,0.993571877 });
	FindGameObjectByName("HB_riverbed 2")->SetScale({ 31,3,156 });
	FindGameObjectByName("HB_riverbed 2")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 15.5, 1.5, 78 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_riverbed 3");
	FindGameObjectByName("HB_riverbed 3")->SetPosition({ -59.873809814,-22.988697052,131.828689575 });
	FindGameObjectByName("HB_riverbed 3")->SetRotation({ 0,0,0,1 });
	FindGameObjectByName("HB_riverbed 3")->SetScale({ 26,6,38 });
	FindGameObjectByName("HB_riverbed 3")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 13, 3, 19 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_riverbed 4");
	FindGameObjectByName("HB_riverbed 4")->SetPosition({ 94.597419739,3.13415575,40.973758698 });
	FindGameObjectByName("HB_riverbed 4")->SetRotation({ 0.04348493,-0.078384265,0.003422331,0.995968521 });
	FindGameObjectByName("HB_riverbed 4")->SetScale({ 41,1,16 });
	FindGameObjectByName("HB_riverbed 4")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 20.5, 0.5, 8 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_riverbed 5");
	FindGameObjectByName("HB_riverbed 5")->SetPosition({ 112.532234192,2.375187397,61.217365265 });
	FindGameObjectByName("HB_riverbed 5")->SetRotation({ 0.07400766,-0.260868132,0.032305066,0.961991191 });
	FindGameObjectByName("HB_riverbed 5")->SetScale({ 51,1,26 });
	FindGameObjectByName("HB_riverbed 5")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 25.5, 0.5, 13 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_riverbed 12");
	FindGameObjectByName("HB_riverbed 12")->SetPosition({ 109.202964783,3.343296051,131.080291748 });
	FindGameObjectByName("HB_riverbed 12")->SetRotation({ -0.146051213,0.116333961,0.01780905,0.982251704 });
	FindGameObjectByName("HB_riverbed 12")->SetScale({ 56,1,19 });
	FindGameObjectByName("HB_riverbed 12")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 28, 0.5, 9.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_riverbed 13");
	FindGameObjectByName("HB_riverbed 13")->SetPosition({ -30.049463272,-17.687412262,-162.696640015 });
	FindGameObjectByName("HB_riverbed 13")->SetRotation({ -0.007215344,-0.025162898,-0.275542885,0.960932374 });
	FindGameObjectByName("HB_riverbed 13")->SetScale({ 1,3,4.800000191 });
	FindGameObjectByName("HB_riverbed 13")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 0.5, 1.5, 2.400000095 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_riverbed 14");
	FindGameObjectByName("HB_riverbed 14")->SetPosition({ -21.553401947,-21.921543121,-195.122344971 });
	FindGameObjectByName("HB_riverbed 14")->SetRotation({ 0,0,0.043619391,0.999048233 });
	FindGameObjectByName("HB_riverbed 14")->SetScale({ 31,1,66 });
	FindGameObjectByName("HB_riverbed 14")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 15.5, 0.5, 33 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_riverbed 15");
	FindGameObjectByName("HB_riverbed 15")->SetPosition({ -30.00762558,-22.379278183,-122.548240662 });
	FindGameObjectByName("HB_riverbed 15")->SetRotation({ 0.000643654,-0.077394411,0.078204013,0.993928492 });
	FindGameObjectByName("HB_riverbed 15")->SetScale({ 21,1,86 });
	FindGameObjectByName("HB_riverbed 15")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 10.5, 0.5, 43 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_riverbed 16");
	FindGameObjectByName("HB_riverbed 16")->SetPosition({ -46.670158386,-23.088510513,-117.602005005 });
	FindGameObjectByName("HB_riverbed 16")->SetRotation({ 0.011927685,-0.092888817,-0.113249213,0.989143133 });
	FindGameObjectByName("HB_riverbed 16")->SetScale({ 21,1,86 });
	FindGameObjectByName("HB_riverbed 16")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 10.5, 0.5, 43 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_riverbed 17");
	FindGameObjectByName("HB_riverbed 17")->SetPosition({ -43.88312912,-21.828807831,-194.359451294 });
	FindGameObjectByName("HB_riverbed 17")->SetRotation({ -0.001602742,0.046356704,-0.059971925,0.997121811 });
	FindGameObjectByName("HB_riverbed 17")->SetScale({ 21,1,76 });
	FindGameObjectByName("HB_riverbed 17")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 10.5, 0.5, 38 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_riverbed 18");
	FindGameObjectByName("HB_riverbed 18")->SetPosition({ -169.232208252,20.674383163,-32.286640167 });
	FindGameObjectByName("HB_riverbed 18")->SetRotation({ 0,0,0,1 });
	FindGameObjectByName("HB_riverbed 18")->SetScale({ 14,14,11 });
	FindGameObjectByName("HB_riverbed 18")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 7, 7, 5.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_riverbed 20");
	FindGameObjectByName("HB_riverbed 20")->SetPosition({ -159.229904175,17.657953262,-30.667161942 });
	FindGameObjectByName("HB_riverbed 20")->SetRotation({ 0,-0.233445331,0,0.972369969 });
	FindGameObjectByName("HB_riverbed 20")->SetScale({ 11,9,10 });
	FindGameObjectByName("HB_riverbed 20")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 5.5, 4.5, 5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_riverbed 21");
	FindGameObjectByName("HB_riverbed 21")->SetPosition({ -148.096633911,16.533658981,-26.684972763 });
	FindGameObjectByName("HB_riverbed 21")->SetRotation({ 0,-0.233445331,0,0.972369969 });
	FindGameObjectByName("HB_riverbed 21")->SetScale({ 16,4,7 });
	FindGameObjectByName("HB_riverbed 21")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8, 2, 3.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_riverbed 22");
	FindGameObjectByName("HB_riverbed 22")->SetPosition({ -141.65045166,18.528486252,-2.937338591 });
	FindGameObjectByName("HB_riverbed 22")->SetRotation({ 0,-0.56640619,0,0.824126244 });
	FindGameObjectByName("HB_riverbed 22")->SetScale({ 14,14,16 });
	FindGameObjectByName("HB_riverbed 22")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 7, 7, 8 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_riverbed 23");
	FindGameObjectByName("HB_riverbed 23")->SetPosition({ -144.532546997,16.342012405,-14.874630928 });
	FindGameObjectByName("HB_riverbed 23")->SetRotation({ -0.052200831,-0.633455992,0.079980657,0.767861784 });
	FindGameObjectByName("HB_riverbed 23")->SetScale({ 14,7,11 });
	FindGameObjectByName("HB_riverbed 23")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 7, 3.5, 5.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_riverbed 24");
	FindGameObjectByName("HB_riverbed 24")->SetPosition({ -268.671264648,0.347371399,101.601074219 });
	FindGameObjectByName("HB_riverbed 24")->SetRotation({ 0,0.258818954,0,0.965925872 });
	FindGameObjectByName("HB_riverbed 24")->SetScale({ 17,6,16 });
	FindGameObjectByName("HB_riverbed 24")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 3, 8 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_riverbed 25");
	FindGameObjectByName("HB_riverbed 25")->SetPosition({ -273.193267822,0.347371399,90.723205566 });
	FindGameObjectByName("HB_riverbed 25")->SetRotation({ 0,0.078458838,0,0.996917367 });
	FindGameObjectByName("HB_riverbed 25")->SetScale({ 16,16,14 });
	FindGameObjectByName("HB_riverbed 25")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8, 8, 7 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_riverbed 26");
	FindGameObjectByName("HB_riverbed 26")->SetPosition({ 177.998916626,-13.290085793,-93.989387512 });
	FindGameObjectByName("HB_riverbed 26")->SetRotation({ 0,0,0,1 });
	FindGameObjectByName("HB_riverbed 26")->SetScale({ 21,11,16 });
	FindGameObjectByName("HB_riverbed 26")->AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 10.5, 5.5, 8 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));

}
