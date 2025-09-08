#include "pch.h"
#include "DevScene.h"
#include "Boulder.h"

#undef max
#undef min
#include <algorithm>

XMFLOAT3 POSITION_BASE = { 325, -2, 50 };


void DevScene::Start()
{
	m_hWnd = mp_sceneManager->GetWindow();

	// Creer le cube (placingModule)
	CreateGameObject("placingModule");
	m_placingModule = GetGameObjectByName("placingModule");
	m_placingModule.SetPosition({ 0, 0, 0 }); // par exemple au centre
	m_placingModule.SetTexture(TEXTURES::NOTEXTURE);

	// Creer la camera
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

	
	CreateEntity("Light2");
	AddComponent<Type_3D>("Light2", new Type_3D());
	AddComponent<MeshComponent>("Light2", new MeshComponent(MESHES::LOCAL_CUBE, TEXTURES::BOIS));
	GetComponent<TransformComponent>("Light2")->position = { 5,20,0 };
	AddComponent<LightComponent>("Light2", new LightComponent(1));
	GetComponent<LightComponent>("Light2")->color = { 1,0,1 };
	GetComponent<LightComponent>("Light2")->direction = { -1, -1, -1 };
	GetComponent<LightComponent>("Light2")->range = 500;

	
	CreateGameObject("Map");
	auto a = GetGameObjectByName("Map");
	a.SetMesh(MESHES::MAP);
	a.SetPosition({ 0,0,0 });
	a.SetScale({ 2,2,2 });

	CreateGameObject("Temple", MESHES::TEMPLE);
	GetGameObjectByName("Temple").SetPosition({ -194,-6,21 });
	GetGameObjectByName("Temple").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Temple").SetScale({ 2,2,2 });



	// HITBOXES TEMPLE
	CreateGameHitbox("HB_Temple 1");
	GetGameObjectByName("HB_Temple 1").SetPosition({ -127,-13,-75 });
	GetGameObjectByName("HB_Temple 1").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 1").SetScale({ 59,18,3 });
	GetGameObjectByName("HB_Temple 1").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 29.5, 9, 1.5 })));
	CreateGameHitbox("HB_Temple 2");
	GetGameObjectByName("HB_Temple 2").SetPosition({ -261,-13,-72 });
	GetGameObjectByName("HB_Temple 2").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 2").SetScale({ 59,18,3 });
	GetGameObjectByName("HB_Temple 2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 29.5, 9, 1.5 })));
	CreateGameHitbox("HB_Temple 3");
	GetGameObjectByName("HB_Temple 3").SetPosition({ -222,-12,117 });
	GetGameObjectByName("HB_Temple 3").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 3").SetScale({ 79,16,3 });
	GetGameObjectByName("HB_Temple 3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 39.5, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 4");
	GetGameObjectByName("HB_Temple 4").SetPosition({ -106,-12,114 });
	GetGameObjectByName("HB_Temple 4").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 4").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 4").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 5");
	GetGameObjectByName("HB_Temple 5").SetPosition({ -175,-12,114 });
	GetGameObjectByName("HB_Temple 5").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 5").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 5").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 6");
	GetGameObjectByName("HB_Temple 6").SetPosition({ -281,-12,117 });
	GetGameObjectByName("HB_Temple 6").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 6").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 6").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 7");
	GetGameObjectByName("HB_Temple 7").SetPosition({ -212,-12,-72 });
	GetGameObjectByName("HB_Temple 7").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 7").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 7").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 8");
	GetGameObjectByName("HB_Temple 8").SetPosition({ -175,-12,-75 });
	GetGameObjectByName("HB_Temple 8").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 8").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 8").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 9");
	GetGameObjectByName("HB_Temple 9").SetPosition({ -130,5,-51 });
	GetGameObjectByName("HB_Temple 9").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 9").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 9").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 10");
	GetGameObjectByName("HB_Temple 10").SetPosition({ -216,5,-48 });
	GetGameObjectByName("HB_Temple 10").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 10").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 10").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 11");
	GetGameObjectByName("HB_Temple 11").SetPosition({ -259,5,39 });
	GetGameObjectByName("HB_Temple 11").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 11").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 11").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 12");
	GetGameObjectByName("HB_Temple 12").SetPosition({ -259,5,8 });
	GetGameObjectByName("HB_Temple 12").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 12").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 12").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 13");
	GetGameObjectByName("HB_Temple 13").SetPosition({ -258,5,94 });
	GetGameObjectByName("HB_Temple 13").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 13").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 13").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 14");
	GetGameObjectByName("HB_Temple 14").SetPosition({ -130,5,90 });
	GetGameObjectByName("HB_Temple 14").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 14").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 14").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 15");
	GetGameObjectByName("HB_Temple 15").SetPosition({ -129,5,35 });
	GetGameObjectByName("HB_Temple 15").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 15").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 15").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 16");
	GetGameObjectByName("HB_Temple 16").SetPosition({ -129,5,4 });
	GetGameObjectByName("HB_Temple 16").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 16").SetScale({ 17,16,3 });
	GetGameObjectByName("HB_Temple 16").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8.5, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 17");
	GetGameObjectByName("HB_Temple 17").SetPosition({ -141,-13,114 });
	GetGameObjectByName("HB_Temple 17").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 17").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 17").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 15, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 18");
	GetGameObjectByName("HB_Temple 18").SetPosition({ -126,-13,99 });
	GetGameObjectByName("HB_Temple 18").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 18").SetScale({ 31,16,3 });
	GetGameObjectByName("HB_Temple 18").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 15.5, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 19");
	GetGameObjectByName("HB_Temple 19").SetPosition({ -168,-13,99 });
	GetGameObjectByName("HB_Temple 19").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 19").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 19").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.750005722, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 20");
	GetGameObjectByName("HB_Temple 20").SetPosition({ -219,-13,104 });
	GetGameObjectByName("HB_Temple 20").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 20").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 20").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.850008011, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 21");
	GetGameObjectByName("HB_Temple 21").SetPosition({ -260,-13,104 });
	GetGameObjectByName("HB_Temple 21").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 21").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 21").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.850008011, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 22");
	GetGameObjectByName("HB_Temple 22").SetPosition({ -261,-13,-57 });
	GetGameObjectByName("HB_Temple 22").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 22").SetScale({ 31,16,3 });
	GetGameObjectByName("HB_Temple 22").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 15.4500103, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 23");
	GetGameObjectByName("HB_Temple 23").SetPosition({ -127,-13,-62 });
	GetGameObjectByName("HB_Temple 23").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 23").SetScale({ 29,16,3 });
	GetGameObjectByName("HB_Temple 23").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.700016022, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 24");
	GetGameObjectByName("HB_Temple 24").SetPosition({ -168,-13,-62 });
	GetGameObjectByName("HB_Temple 24").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 24").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 24").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.850019455, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 25");
	GetGameObjectByName("HB_Temple 25").SetPosition({ -219,-13,-57 });
	GetGameObjectByName("HB_Temple 25").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 25").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 25").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.850019455, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 26");
	GetGameObjectByName("HB_Temple 26").SetPosition({ -165,4,-51 });
	GetGameObjectByName("HB_Temple 26").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 26").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 26").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.850019455, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 27");
	GetGameObjectByName("HB_Temple 27").SetPosition({ -251,4,-48 });
	GetGameObjectByName("HB_Temple 27").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 27").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 27").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 28");
	GetGameObjectByName("HB_Temple 28").SetPosition({ -164,4,90 });
	GetGameObjectByName("HB_Temple 28").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 28").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 28").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 29");
	GetGameObjectByName("HB_Temple 29").SetPosition({ -223,4,93 });
	GetGameObjectByName("HB_Temple 29").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 29").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 29").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 30");
	GetGameObjectByName("HB_Temple 30").SetPosition({ -162,22,-25 });
	GetGameObjectByName("HB_Temple 30").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 30").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 30").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 31");
	GetGameObjectByName("HB_Temple 31").SetPosition({ -226,22,-24 });
	GetGameObjectByName("HB_Temple 31").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 31").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 31").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 32");
	GetGameObjectByName("HB_Temple 32").SetPosition({ -226,22,66 });
	GetGameObjectByName("HB_Temple 32").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 32").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 32").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 33");
	GetGameObjectByName("HB_Temple 33").SetPosition({ -162,22,66 });
	GetGameObjectByName("HB_Temple 33").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 33").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 33").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	
	CreateGameHitbox("HB_Temple 42");
	GetGameObjectByName("HB_Temple 42").SetPosition({ -275,-13,-44 });
	GetGameObjectByName("HB_Temple 42").SetRotation({ 0,-0.707106709,0,0.707106829 });
	GetGameObjectByName("HB_Temple 42").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 42").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	CreateGameHitbox("HB_Temple 43");
	GetGameObjectByName("HB_Temple 43").SetPosition({ -114,-13,-48 });
	GetGameObjectByName("HB_Temple 43").SetRotation({ 0,-0.707106709,0,0.707106829 });
	GetGameObjectByName("HB_Temple 43").SetScale({ 30,16,3 });
	GetGameObjectByName("HB_Temple 43").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.950021744, 8, 1.5 })));
	
	CreateGameHitbox("HB_Temple 50");
	GetGameObjectByName("HB_Temple 50").SetPosition({ -100,-12,72 });
	GetGameObjectByName("HB_Temple 50").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 50").SetScale({ 3,16,86 });
	GetGameObjectByName("HB_Temple 50").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 43 })));
	CreateGameHitbox("HB_Temple 51");
	GetGameObjectByName("HB_Temple 51").SetPosition({ -99,-12,-33 });
	GetGameObjectByName("HB_Temple 51").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 51").SetScale({ 3,16,86 });
	GetGameObjectByName("HB_Temple 51").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 43 })));
	CreateGameHitbox("HB_Temple 52");
	GetGameObjectByName("HB_Temple 52").SetPosition({ -288,-12,-29 });
	GetGameObjectByName("HB_Temple 52").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 52").SetScale({ 3,16,86 });
	GetGameObjectByName("HB_Temple 52").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 43 })));
	CreateGameHitbox("HB_Temple 53");
	GetGameObjectByName("HB_Temple 53").SetPosition({ -288,-12,76 });
	GetGameObjectByName("HB_Temple 53").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 53").SetScale({ 3,16,86 });
	GetGameObjectByName("HB_Temple 53").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 43 })));
	
	CreateGameHitbox("HB_Temple 54");
	GetGameObjectByName("HB_Temple 54").SetPosition({ -123,4,42 });
	GetGameObjectByName("HB_Temple 54").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 54").SetScale({ 3,16,16 });
	GetGameObjectByName("HB_Temple 54").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 8 })));
	CreateGameHitbox("HB_Temple 55");
	GetGameObjectByName("HB_Temple 55").SetPosition({ -123,4,-45 });
	GetGameObjectByName("HB_Temple 55").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 55").SetScale({ 3,16,16 });
	GetGameObjectByName("HB_Temple 55").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 8.199993134 })));
	CreateGameHitbox("HB_Temple 56");
	GetGameObjectByName("HB_Temple 56").SetPosition({ -265,4,45 });
	GetGameObjectByName("HB_Temple 56").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 56").SetScale({ 3,16,16 });
	GetGameObjectByName("HB_Temple 56").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 8.199993134 })));
	CreateGameHitbox("HB_Temple 57");
	GetGameObjectByName("HB_Temple 57").SetPosition({ -264,4,-41 });
	GetGameObjectByName("HB_Temple 57").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 57").SetScale({ 3,16,16 });
	GetGameObjectByName("HB_Temple 57").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 8.199993134 })));
	CreateGameHitbox("HB_Temple 58");
	GetGameObjectByName("HB_Temple 58").SetPosition({ -264.345916748,5.172028542,-6.902385235 });
	GetGameObjectByName("HB_Temple 58").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 58").SetScale({ 3,18,28 });
	GetGameObjectByName("HB_Temple 58").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 9, 14 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_Temple 59");
	GetGameObjectByName("HB_Temple 59").SetPosition({ -264.689819336,5.172028542,79.01007843 });
	GetGameObjectByName("HB_Temple 59").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_Temple 59").SetScale({ 3,18,28 });
	GetGameObjectByName("HB_Temple 59").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 9, 14 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	//

	CreateGameHitbox("HB_T_suite 1");
	GetGameObjectByName("HB_T_suite 1").SetPosition({ -116.240844727,-3.04857111,-33.811027527 });
	GetGameObjectByName("HB_T_suite 1").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 1").SetScale({ 41.020000458,2.019999981,90.020004272 });
	GetGameObjectByName("HB_T_suite 1").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 20.510000229, 1.00999999, 45.010002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 3");
	GetGameObjectByName("HB_T_suite 3").SetPosition({ -116.585662842,-3.04857111,71.859550476 });
	GetGameObjectByName("HB_T_suite 3").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 3").SetScale({ 41.020000458,2.019999981,90.020004272 });
	GetGameObjectByName("HB_T_suite 3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 20.510000229, 1.00999999, 45.010002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 4");
	GetGameObjectByName("HB_T_suite 4").SetPosition({ -271.021453857,-3.04857111,-30.085664749 });
	GetGameObjectByName("HB_T_suite 4").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 4").SetScale({ 41.020000458,2.019999981,90.020004272 });
	GetGameObjectByName("HB_T_suite 4").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 20.510000229, 1.00999999, 45.010002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 5");
	GetGameObjectByName("HB_T_suite 5").SetPosition({ -271.206054688,-3.04857111,75.994880676 });
	GetGameObjectByName("HB_T_suite 5").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 5").SetScale({ 41.020000458,2.019999981,90.020004272 });
	GetGameObjectByName("HB_T_suite 5").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 20.510000229, 1.00999999, 45.010002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 6");
	GetGameObjectByName("HB_T_suite 6").SetPosition({ -161.185165405,-3.02259922,-58.053150177 });
	GetGameObjectByName("HB_T_suite 6").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 6").SetScale({ 49.020000458,2.019999981,41.020004272 });
	GetGameObjectByName("HB_T_suite 6").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 24.510000229, 1.00999999, 20.510002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 7");
	GetGameObjectByName("HB_T_suite 7").SetPosition({ -161.249969482,-3.02259922,96.368858337 });
	GetGameObjectByName("HB_T_suite 7").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 7").SetScale({ 49.020000458,2.019999981,41.020004272 });
	GetGameObjectByName("HB_T_suite 7").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 24.510000229, 1.00999999, 20.510002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 8");
	GetGameObjectByName("HB_T_suite 8").SetPosition({ -226.159378052,-3.02259922,100.080795288 });
	GetGameObjectByName("HB_T_suite 8").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 8").SetScale({ 49.020000458,2.019999981,41.020004272 });
	GetGameObjectByName("HB_T_suite 8").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 24.510000229, 1.00999999, 20.510002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 9");
	GetGameObjectByName("HB_T_suite 9").SetPosition({ -226.342651367,-3.02259922,-54.448307037 });
	GetGameObjectByName("HB_T_suite 9").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 9").SetScale({ 49.020000458,2.019999981,41.020004272 });
	GetGameObjectByName("HB_T_suite 9").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 24.510000229, 1.00999999, 20.510002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 10");
	GetGameObjectByName("HB_T_suite 10").SetPosition({ -134.130508423,13.72262001,60.743515015 });
	GetGameObjectByName("HB_T_suite 10").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 10").SetScale({ 29.020000458,2.019999981,66.020004272 });
	GetGameObjectByName("HB_T_suite 10").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.510000229, 1.00999999, 33.010002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 11");
	GetGameObjectByName("HB_T_suite 11").SetPosition({ -133.577651978,13.72262001,-23.204435349 });
	GetGameObjectByName("HB_T_suite 11").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 11").SetScale({ 29.020000458,2.019999981,66.020004272 });
	GetGameObjectByName("HB_T_suite 11").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.510000229, 1.00999999, 33.010002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 12");
	GetGameObjectByName("HB_T_suite 12").SetPosition({ -253.671920776,13.72262001,-18.691040039 });
	GetGameObjectByName("HB_T_suite 12").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 12").SetScale({ 29.020000458,2.019999981,66.020004272 });
	GetGameObjectByName("HB_T_suite 12").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.510000229, 1.00999999, 33.010002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 13");
	GetGameObjectByName("HB_T_suite 13").SetPosition({ -254.026412964,13.72262001,65.354766846 });
	GetGameObjectByName("HB_T_suite 13").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 13").SetScale({ 29.020000458,2.019999981,66.020004272 });
	GetGameObjectByName("HB_T_suite 13").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 14.510000229, 1.00999999, 33.010002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 15");
	GetGameObjectByName("HB_T_suite 15").SetPosition({ -222.184890747,13.72163105,82.829498291 });
	GetGameObjectByName("HB_T_suite 15").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 15").SetScale({ 39.020000458,2.019999981,31.020004272 });
	GetGameObjectByName("HB_T_suite 15").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 19.510000229, 1.00999999, 15.510002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 16");
	GetGameObjectByName("HB_T_suite 16").SetPosition({ -165.030487061,13.72163105,78.251525879 });
	GetGameObjectByName("HB_T_suite 16").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 16").SetScale({ 39.020000458,2.019999981,31.020004272 });
	GetGameObjectByName("HB_T_suite 16").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 19.510000229, 1.00999999, 15.510002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 17");
	GetGameObjectByName("HB_T_suite 17").SetPosition({ -165.429290771,13.71800518,-40.653587341 });
	GetGameObjectByName("HB_T_suite 17").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 17").SetScale({ 39.020000458,2.019999981,31.020004272 });
	GetGameObjectByName("HB_T_suite 17").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 19.510000229, 1.00999999, 15.510002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 18");
	GetGameObjectByName("HB_T_suite 18").SetPosition({ -222.511566162,13.71800518,-36.133331299 });
	GetGameObjectByName("HB_T_suite 18").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 18").SetScale({ 39.020000458,2.019999981,31.020004272 });
	GetGameObjectByName("HB_T_suite 18").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 19.510000229, 1.00999999, 15.510002136 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 19");
	GetGameObjectByName("HB_T_suite 19").SetPosition({ -178.514648438,5.46626091,-43.518615723 });
	GetGameObjectByName("HB_T_suite 19").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 19").SetScale({ 2,15,12 });
	GetGameObjectByName("HB_T_suite 19").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1, 7.5, 6 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 20");
	GetGameObjectByName("HB_T_suite 20").SetPosition({ -209.276000977,5.46626091,-40.153446198 });
	GetGameObjectByName("HB_T_suite 20").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 20").SetScale({ 2,15,12 });
	GetGameObjectByName("HB_T_suite 20").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1, 7.5, 6 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 21");
	GetGameObjectByName("HB_T_suite 21").SetPosition({ -209.25050354,5.46626091,85.676063538 });
	GetGameObjectByName("HB_T_suite 21").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 21").SetScale({ 2,15,12 });
	GetGameObjectByName("HB_T_suite 21").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1, 7.5, 6 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 23");
	GetGameObjectByName("HB_T_suite 23").SetPosition({ -178.272338867,5.46626091,81.982406616 });
	GetGameObjectByName("HB_T_suite 23").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 23").SetScale({ 2,15,12 });
	GetGameObjectByName("HB_T_suite 23").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1, 7.5, 6 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 24");
	GetGameObjectByName("HB_T_suite 24").SetPosition({ -250.947143555,-1.396932125,-12.716756821 });
	GetGameObjectByName("HB_T_suite 24").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 24").SetScale({ 1,4,42 });
	GetGameObjectByName("HB_T_suite 24").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 0.5, 2, 21 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 25");
	GetGameObjectByName("HB_T_suite 25").SetPosition({ -250.99571228,-1.396932125,58.372711182 });
	GetGameObjectByName("HB_T_suite 25").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 25").SetScale({ 1,4,42 });
	GetGameObjectByName("HB_T_suite 25").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 0.5, 2, 21 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 26");
	GetGameObjectByName("HB_T_suite 26").SetPosition({ -137.026489258,-1.396932125,-16.265182495 });
	GetGameObjectByName("HB_T_suite 26").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 26").SetScale({ 1,4,42 });
	GetGameObjectByName("HB_T_suite 26").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 0.5, 2, 21 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 27");
	GetGameObjectByName("HB_T_suite 27").SetPosition({ -136.784561157,-1.396932125,54.801616669 });
	GetGameObjectByName("HB_T_suite 27").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 27").SetScale({ 1,4,42 });
	GetGameObjectByName("HB_T_suite 27").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 0.5, 2, 21 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 29");
	GetGameObjectByName("HB_T_suite 29").SetPosition({ -229.908630371,-1.41100502,-33.778793335 });
	GetGameObjectByName("HB_T_suite 29").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 29").SetScale({ 43,4,1 });
	GetGameObjectByName("HB_T_suite 29").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 21.5, 2, 0.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 30");
	GetGameObjectByName("HB_T_suite 30").SetPosition({ -158.026245117,-1.41100502,-37.509101868 });
	GetGameObjectByName("HB_T_suite 30").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 30").SetScale({ 43,4,1 });
	GetGameObjectByName("HB_T_suite 30").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 21.5, 2, 0.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 31");
	GetGameObjectByName("HB_T_suite 31").SetPosition({ -157.802932739,-1.41100502,75.952987671 });
	GetGameObjectByName("HB_T_suite 31").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 31").SetScale({ 43,4,1 });
	GetGameObjectByName("HB_T_suite 31").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 21.5, 2, 0.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 32");
	GetGameObjectByName("HB_T_suite 32").SetPosition({ -229.949813843,-1.41100502,79.702590942 });
	GetGameObjectByName("HB_T_suite 32").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 32").SetScale({ 43,4,1 });
	GetGameObjectByName("HB_T_suite 32").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 21.5, 2, 0.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 34");
	GetGameObjectByName("HB_T_suite 34").SetPosition({ -194.001220703,32.213443756,59.79094696 });
	GetGameObjectByName("HB_T_suite 34").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 34").SetScale({ 96,1,16 });
	GetGameObjectByName("HB_T_suite 34").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 48, 0.5, 8 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));

	CreateGameHitbox("HB_T_suite 36");
	GetGameObjectByName("HB_T_suite 36").SetPosition({ -155.857131958,32.196475983,21.051273346 });
	GetGameObjectByName("HB_T_suite 36").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 36").SetScale({ 19,1,66 });
	GetGameObjectByName("HB_T_suite 36").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 9.5, 0.5, 33 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite 37");
	GetGameObjectByName("HB_T_suite 37").SetPosition({ -232.756973267,32.196475983,22.633777618 });
	GetGameObjectByName("HB_T_suite 37").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite 37").SetScale({ 19,1,66 });
	GetGameObjectByName("HB_T_suite 37").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 9.5, 0.5, 33 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));

	
	CreateGameHitbox("HB_T_suite2 4");
	GetGameObjectByName("HB_T_suite2 4").SetPosition({ -274.899505615,-11.484270096,-2.228993893 });
	GetGameObjectByName("HB_T_suite2 4").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 4").SetScale({ 3,16,31 });
	GetGameObjectByName("HB_T_suite2 4").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 5");
	GetGameObjectByName("HB_T_suite2 5").SetPosition({ -273.622650146,-11.484270096,48.560863495 });
	GetGameObjectByName("HB_T_suite2 5").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 5").SetScale({ 3,16,31 });
	GetGameObjectByName("HB_T_suite2 5").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 6");
	GetGameObjectByName("HB_T_suite2 6").SetPosition({ -273.612091064,-11.484270096,90.027816772 });
	GetGameObjectByName("HB_T_suite2 6").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 6").SetScale({ 3,16,31 });
	GetGameObjectByName("HB_T_suite2 6").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 7");
	GetGameObjectByName("HB_T_suite2 7").SetPosition({ -112.599578857,-11.484270096,44.185222626 });
	GetGameObjectByName("HB_T_suite2 7").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 7").SetScale({ 3,16,31 });
	GetGameObjectByName("HB_T_suite2 7").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 8");
	GetGameObjectByName("HB_T_suite2 8").SetPosition({ -112.63419342,-11.484270096,85.598518372 });
	GetGameObjectByName("HB_T_suite2 8").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 8").SetScale({ 3,16,31 });
	GetGameObjectByName("HB_T_suite2 8").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 9");
	GetGameObjectByName("HB_T_suite2 9").SetPosition({ -113.955566406,-11.484270096,-6.917423725 });
	GetGameObjectByName("HB_T_suite2 9").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 9").SetScale({ 3,16,31 });
	GetGameObjectByName("HB_T_suite2 9").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 10");
	GetGameObjectByName("HB_T_suite2 10").SetPosition({ -122.988365173,4.453486919,-10.090456009 });
	GetGameObjectByName("HB_T_suite2 10").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 10").SetScale({ 3,16,31 });
	GetGameObjectByName("HB_T_suite2 10").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 11");
	GetGameObjectByName("HB_T_suite2 11").SetPosition({ -123.226417542,4.453486919,75.959533691 });
	GetGameObjectByName("HB_T_suite2 11").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 11").SetScale({ 3,16,31 });
	GetGameObjectByName("HB_T_suite2 11").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 12");
	GetGameObjectByName("HB_T_suite2 12").SetPosition({ -148.065490723,22.411590576,52.032306671 });
	GetGameObjectByName("HB_T_suite2 12").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 12").SetScale({ 3,17,31 });
	GetGameObjectByName("HB_T_suite2 12").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8.5, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 13");
	GetGameObjectByName("HB_T_suite2 13").SetPosition({ -148.069961548,22.411590576,-10.634102821 });
	GetGameObjectByName("HB_T_suite2 13").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 13").SetScale({ 3,17,31 });
	GetGameObjectByName("HB_T_suite2 13").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8.5, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 14");
	GetGameObjectByName("HB_T_suite2 14").SetPosition({ -239.49961853,22.411590576,-9.832740784 });
	GetGameObjectByName("HB_T_suite2 14").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 14").SetScale({ 3,17,31 });
	GetGameObjectByName("HB_T_suite2 14").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8.5, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 15");
	GetGameObjectByName("HB_T_suite2 15").SetPosition({ -239.695678711,22.411590576,51.847362518 });
	GetGameObjectByName("HB_T_suite2 15").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 15").SetScale({ 3,17,31 });
	GetGameObjectByName("HB_T_suite2 15").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 1.5, 8.5, 15.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));
	CreateGameHitbox("HB_T_suite2 16");
	GetGameObjectByName("HB_T_suite2 16").SetPosition({ -193.999481201,32.187534332,-15.832008362 });
	GetGameObjectByName("HB_T_suite2 16").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_T_suite2 16").SetScale({ 96,1,21 });
	GetGameObjectByName("HB_T_suite2 16").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 48, 0.5, 10.5 }, { 0, 0, 0, 1 }, { 0, 0, 0 })));





	CreateGameObject("repere 1", MESHES::LOCAL_CUBE, 0);
	GetGameObjectByName("repere 1").SetPosition({ -72,-16,116 });
	GetGameObjectByName("repere 1").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("repere 1").SetScale({ 1,5,1 });

	CreateGameObject("repere 2", MESHES::LOCAL_CUBE, 0);
	GetGameObjectByName("repere 2").SetPosition({ 235,-17,-68 });
	GetGameObjectByName("repere 2").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("repere 2").SetScale({ 1,5,1 });

	CreateGameHitbox("HB 1"); // start zone 1
	GetGameObjectByName("HB 1").SetPosition({ 220,-23,-132 });
	GetGameObjectByName("HB 1").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB 1").SetScale({ 326,6,206 });
	GetGameObjectByName("HB 1").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 163, 3, 103 })));
	CreateGameHitbox("HB 2");// start zone 2
	GetGameObjectByName("HB 2").SetPosition({ 28,-23,-134 });
	GetGameObjectByName("HB 2").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB 2").SetScale({ 76,6,206 });
	GetGameObjectByName("HB 2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 38, 3, 103 })));
	CreateGameHitbox("HB 3");// temple zone 
	GetGameObjectByName("HB 3").SetPosition({ -208,-23,-30 });
	GetGameObjectByName("HB 3").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB 3").SetScale({ 271,6,421 });
	GetGameObjectByName("HB 3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 135.5, 3, 210.5 })));
	CreateGameHitbox("HB 4");// deep lac + river
	GetGameObjectByName("HB 4").SetPosition({ -5,-30,-29 });
	GetGameObjectByName("HB 4").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB 4").SetScale({ 156,6,416 });
	GetGameObjectByName("HB 4").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 78, 3, 208 })));
	CreateGameHitbox("HB 5");// RockWall
	GetGameObjectByName("HB 5").SetPosition({ 206,-3,-32 });
	GetGameObjectByName("HB 5").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB 5").SetScale({ 276,41,46 });
	GetGameObjectByName("HB 5").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 138, 20.5, 23 })));


	CreateGameHitbox("HB_ 1"); // right side map 1
	GetGameObjectByName("HB_ 1").SetPosition({ 355,3,-153 });
	GetGameObjectByName("HB_ 1").SetRotation({ 0,-0.104528427,0,0.994521916 });
	GetGameObjectByName("HB_ 1").SetScale({ 11,51,176 });
	GetGameObjectByName("HB_ 1").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 5.5, 25.5, 88 })));
	CreateGameHitbox("HB_ 2");// right side map 2
	GetGameObjectByName("HB_ 2").SetPosition({ 340,31,47 });
	GetGameObjectByName("HB_ 2").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_ 2").SetScale({ 16,111,246 });
	GetGameObjectByName("HB_ 2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 8, 55.5, 123 })));
	CreateGameHitbox("HB_ 3");// far side map 1 (up hill)
	GetGameObjectByName("HB_ 3").SetPosition({ 303,31,168 });
	GetGameObjectByName("HB_ 3").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_ 3").SetScale({ 71,86,11 });
	GetGameObjectByName("HB_ 3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 35.5, 43, 5.5 })));
	CreateGameHitbox("HB_ 4");// far side map 2
	GetGameObjectByName("HB_ 4").SetPosition({ 210,31,161 });
	GetGameObjectByName("HB_ 4").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_ 4").SetScale({ 133,86,11 });
	GetGameObjectByName("HB_ 4").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 66.5, 43, 5.5 })));
	CreateGameHitbox("HB_ 5");// far side map 3
	GetGameObjectByName("HB_ 5").SetPosition({ 69,31,163 });
	GetGameObjectByName("HB_ 5").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_ 5").SetScale({ 153,106,11 });
	GetGameObjectByName("HB_ 5").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 76.5, 53, 5.5 })));
	CreateGameHitbox("HB_ 6");// far side map 4
	GetGameObjectByName("HB_ 6").SetPosition({ -158,19,156 });
	GetGameObjectByName("HB_ 6").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_ 6").SetScale({ 313,106,11 });
	GetGameObjectByName("HB_ 6").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 156.5, 53, 5.5 })));
	CreateGameHitbox("HB_ 7");// left side map
	GetGameObjectByName("HB_ 7").SetPosition({ -307,19,-18 });
	GetGameObjectByName("HB_ 7").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("HB_ 7").SetScale({ 18,106,436 });
	GetGameObjectByName("HB_ 7").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 9, 53, 218 })));
	CreateGameHitbox("HB_ 8");// close side map 1 (down hill)
	GetGameObjectByName("HB_ 8").SetPosition({ 34,2,-238 });
	GetGameObjectByName("HB_ 8").SetRotation({ 0,0.713250458,0,0.700909257 });
	GetGameObjectByName("HB_ 8").SetScale({ 18,96,741 });
	GetGameObjectByName("HB_ 8").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ 9, 48, 370.5 })));






	CreateGameObject("RockWall 0", 35, 4294967295);
	GetGameObjectByName("RockWall 0").SetPosition({ -32,-18,-163 });
	GetGameObjectByName("RockWall 0").SetRotation({ 0,-0.078459084,0,0.996917367 });
	GetGameObjectByName("RockWall 0").SetScale({ 1,1,2 });
	CreateGameObject("RockWall 1", 17, 4294967295);
	GetGameObjectByName("RockWall 1").SetPosition({ 57,2,-19 });
	GetGameObjectByName("RockWall 1").SetRotation({ 0,-0.078459084,0,0.996917367 });
	GetGameObjectByName("RockWall 1").SetScale({ 25,16,26 });
	CreateGameObject("RockWall 2", 17, 4294967295);
	GetGameObjectByName("RockWall 2").SetPosition({ 10,2,-58 });
	GetGameObjectByName("RockWall 2").SetRotation({ 0,-0.544638991,0,0.838670671 });
	GetGameObjectByName("RockWall 2").SetScale({ 29,25,30 });
	CreateGameObject("RockWall 3", 18, 4294967295);
	GetGameObjectByName("RockWall 3").SetPosition({ 38,-16,16 });
	GetGameObjectByName("RockWall 3").SetRotation({ 0,0.96126163,0,0.275637567 });
	GetGameObjectByName("RockWall 3").SetScale({ 48,35,40 });
	CreateGameObject("RockWall 5", 19, 4294967295);
	GetGameObjectByName("RockWall 5").SetPosition({ -57,2,-59 });
	GetGameObjectByName("RockWall 5").SetRotation({ 0,0.96126163,0,0.275637567 });
	GetGameObjectByName("RockWall 5").SetScale({ 43,80,35 });
	CreateGameObject("RockWall 6", 17, 4294967295);
	GetGameObjectByName("RockWall 6").SetPosition({ -3,-18,-8 });
	GetGameObjectByName("RockWall 6").SetRotation({ 0.557308376,0.05808115,0.254369915,0.788244784 });
	GetGameObjectByName("RockWall 6").SetScale({ 31,13,26 });

	CreateGameObject("Boulder 0", 18, 4294967295);
	GetGameObjectByName("Boulder 0").SetPosition({ -53,-21,113 });
	GetGameObjectByName("Boulder 0").SetRotation({ 0.583064735,-0.467740774,0.46044904,0.478790939 });
	GetGameObjectByName("Boulder 0").SetScale({ 11,11,11 });
	CreateGameObject("Boulder 1", 18, 4294967295);
	GetGameObjectByName("Boulder 1").SetPosition({ -39,-21,111 });
	GetGameObjectByName("Boulder 1").SetRotation({ 0.113225348,-0.030704228,0.993081927,-0.00505937 });
	GetGameObjectByName("Boulder 1").SetScale({ 7,20,9 });
	CreateGameObject("Boulder 2", 18, 4294967295);
	GetGameObjectByName("Boulder 2").SetPosition({ -20,-19,111 });
	GetGameObjectByName("Boulder 2").SetRotation({ 0.076485023,0.680503786,0.723926127,-0.083639987 });
	GetGameObjectByName("Boulder 2").SetScale({ 6,14,19 });
	CreateGameObject("BigRock", 20, 4294967295);
	GetGameObjectByName("BigRock").SetPosition({ 9,-6,147 });
	GetGameObjectByName("BigRock").SetRotation({ 0,-0.878817022,0,0.477158964 });
	GetGameObjectByName("BigRock").SetScale({ 36,41,41 });


	// CHAMPS
	CreateGameObject("Champs 0", 2, 33);
	GetGameObjectByName("Champs 0").SetPosition({ 239,-20,-131 });
	GetGameObjectByName("Champs 0").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Champs 0").SetScale({ 150,2,100 });
	CreateGameObject("Maison", 4, 1);
	GetGameObjectByName("Maison").SetPosition({ 178,-19,-94 });
	GetGameObjectByName("Maison").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Maison").SetScale({ 2,2,2 });
	CreateGameObject("Champs 2", 2, 7);
	GetGameObjectByName("Champs 2").SetPosition({ 253,-19,-99 });
	GetGameObjectByName("Champs 2").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Champs 2").SetScale({ 110,2,25 });
	CreateGameObject("Champs 3", 2, 7);
	GetGameObjectByName("Champs 3").SetPosition({ 253,-19,-132 });
	GetGameObjectByName("Champs 3").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Champs 3").SetScale({ 110,2,25 });
	CreateGameObject("Champs 4", 2, 7);
	GetGameObjectByName("Champs 4").SetPosition({ 253,-19,-164 });
	GetGameObjectByName("Champs 4").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Champs 4").SetScale({ 110,2,25 });

	// OLIVIERS DECO
	CreateGameObject("Tree 8", 34, 4294967295);
	GetGameObjectByName("Tree 8").SetPosition({ 8,91,-61 });
	GetGameObjectByName("Tree 8").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Tree 8").SetScale({ 16,16,16 });
	CreateGameObject("Tree 9", 34, 4294967295);
	GetGameObjectByName("Tree 9").SetPosition({ 101,1,-92 });
	GetGameObjectByName("Tree 9").SetRotation({ 0,-0.788010716,0,0.615661561 });
	GetGameObjectByName("Tree 9").SetScale({ 6,6,6 });
	CreateGameObject("Tree 10", 34, 4294967295);
	GetGameObjectByName("Tree 10").SetPosition({ 329,1,-196 });
	GetGameObjectByName("Tree 10").SetRotation({ 0,-0.882947743,0,-0.469471335 });
	GetGameObjectByName("Tree 10").SetScale({ 6,6,6 });
	CreateGameObject("Tree 11", 34, 4294967295);
	GetGameObjectByName("Tree 11").SetPosition({ 255,27,-2 });
	GetGameObjectByName("Tree 11").SetRotation({ 0,-0.882947743,0,-0.469471335 });
	GetGameObjectByName("Tree 11").SetScale({ 6,6,6 });
	CreateGameObject("Tree 12", 34, 4294967295);
	GetGameObjectByName("Tree 12").SetPosition({ 281,28,91 });
	GetGameObjectByName("Tree 12").SetRotation({ 0,0.15643461,0,0.987688363 });
	GetGameObjectByName("Tree 12").SetScale({ 7,7,7 });

	CreateGameObject("Olivier_trunk 13", 32, 4294967295);
	GetGameObjectByName("Olivier_trunk 13").SetPosition({ -79,-22,-115 });
	GetGameObjectByName("Olivier_trunk 13").SetRotation({ 0,0.656059146,0,0.754709542 });
	GetGameObjectByName("Olivier_trunk 13").SetScale({ 7,7,7 });

	CreateGameObject("Tree 16", 34, 4294967295);
	GetGameObjectByName("Tree 16").SetPosition({ -47,6,-232 });
	GetGameObjectByName("Tree 16").SetRotation({ -0.138627812,-0.479704678,-0.037643887,0.865591586 });
	GetGameObjectByName("Tree 16").SetScale({ 8,8,8 });

	// ARBRES CHAMPS
	CreateGameObject("Tree 17", 28, 4294967295);
	GetGameObjectByName("Tree 17").SetPosition({ 308,-7,-179 });
	GetGameObjectByName("Tree 17").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Tree 17").SetScale({ 2,2,2 });
	CreateGameObject("Tree 18", 28, 4294967295);
	GetGameObjectByName("Tree 18").SetPosition({ 307,-7,-84 });
	GetGameObjectByName("Tree 18").SetRotation({ 0,0,0,1 });
	GetGameObjectByName("Tree 18").SetScale({ 2,2,2 });
	CreateGameObject("Tree 19", 28, 4294967295);
	GetGameObjectByName("Tree 19").SetPosition({ 167,-7,-83 });
	GetGameObjectByName("Tree 19").SetRotation({ 0,0.999048233,0,-0.043619186 });
	GetGameObjectByName("Tree 19").SetScale({ 2,2,2 });
	CreateGameObject("Tree 20", 28, 4294967295);
	GetGameObjectByName("Tree 20").SetPosition({ 168,-7,-178 });
	GetGameObjectByName("Tree 20").SetRotation({ 0,0.999048233,0,-0.043619186 });
	GetGameObjectByName("Tree 20").SetScale({ 2,2,2 });

	// OLIVES COMPETENCE
	CreateGameObject("Olivier_trunk 23", 32, 4294967295);// 1
	GetGameObjectByName("Olivier_trunk 23").SetPosition({ 72,1,149 });
	GetGameObjectByName("Olivier_trunk 23").SetRotation({ -0.015740039,-0.043857157,0.012615366,0.998834133 });
	GetGameObjectByName("Olivier_trunk 23").SetScale({ 4,4,4 });
	CreateGameObject("Olivier_leaves 22", 33, 4294967295); 
	GetGameObjectByName("Olivier_leaves 22").SetPosition({ 53,-9,128 });
	GetGameObjectByName("Olivier_leaves 22").SetRotation({ -0.040849205,-0.022417387,0.671295822,0.739723504 });
	GetGameObjectByName("Olivier_leaves 22").SetScale({ 4,4,4 });

	CreateGameObject("Olivier_trunk 21", 32, 4294967295);// 2
	GetGameObjectByName("Olivier_trunk 21").SetPosition({ -14,2,-21 });
	GetGameObjectByName("Olivier_trunk 21").SetRotation({ 0,0.737277627,0,-0.675589979 });
	GetGameObjectByName("Olivier_trunk 21").SetScale({ 6,7,7 });
	CreateGameObject("Olivier_leaves 24", 33, 4294967295);
	GetGameObjectByName("Olivier_leaves 24").SetPosition({ -59,-8,-17 });
	GetGameObjectByName("Olivier_leaves 24").SetRotation({ 0.03906719,-0.74653542,-0.012860671,0.664073229 });
	GetGameObjectByName("Olivier_leaves 24").SetScale({ 6,6,7 });


	// TEST TOUS LES MESHS
	//int i = MESHES::Temple;
	//float j = 0;
	//for (; i < MESHES::TotalMeshCount; i++)
	//{
	//	auto b = CreateGameObject("", i);
	//	 //= GetGameObjectByName("");
	//	b.SetScale({ 10,10,10 });
	//	b.SetPosition({ -150 + 50.f * j,0,0 });
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
		m_camSpeed = m_camWalkSpeed / 30;
		m_scaleSpeed = 0.01;
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
					//std::string cm_position = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\").SetPosition({ " + RoundValueStr(gm->GetPosition().x) + "," + RoundValueStr(gm->GetPosition().y) + "," + RoundValueStr(gm->GetPosition().z) + " });";
					std::string cm_position = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\").SetPosition({ " + FloatToStringNoTrailingZeros(gm->GetPosition().x) + "," + FloatToStringNoTrailingZeros(gm->GetPosition().y) + "," + FloatToStringNoTrailingZeros(gm->GetPosition().z) + " });";
					std::string cm_rotation = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\").SetRotation({ " + FloatToStringNoTrailingZeros(gm->GetRotation().x) + "," + FloatToStringNoTrailingZeros(gm->GetRotation().y) + "," + FloatToStringNoTrailingZeros(gm->GetRotation().z) + "," + FloatToStringNoTrailingZeros(gm->GetRotation().w) + " });";
					//std::string cm_scale = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\").SetScale({ " + RoundValueStr(gm->GetScale().x) + "," + RoundValueStr(gm->GetScale().y) + "," + RoundValueStr(gm->GetScale().z) + " });";
					std::string cm_scale = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\").SetScale({ " + FloatToStringNoTrailingZeros(gm->GetScale().x) + "," + FloatToStringNoTrailingZeros(gm->GetScale().y) + "," + FloatToStringNoTrailingZeros(gm->GetScale().z) + " });";
					std::string cm_collider = std::string("\nGetGameObjectByName(\"") + gm->GetName()
						+ "\").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ "
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
			//m_placingModule.SetTexture(0);

			m_curMeshID -= 1;
			if (m_curMeshID < 0)
				m_curMeshID = MESHES::TotalMeshCount - 1;
			if (m_curMeshID >= MESHES::TEMPLE)
				m_curTexID = UINT_MAX;
			else
				m_curTexID = TEXTURES::NOTEXTURE;
			m_placingModule.SetTexture(m_curTexID);
			m_placingModule.SetMesh(m_curMeshID);
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
			m_placingModule.SetTexture(m_curTexID);
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