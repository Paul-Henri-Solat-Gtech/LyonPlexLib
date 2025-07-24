#include "pch.h"
#include "DevScene.h"

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

	//// Cr馥r le ground, etc.
	//CreateGameObject("ground", 2, 3);
	//GetGameObjectByName("ground").SetPosition({ 0, -2, 0 });
	//GetGameObjectByName("ground").SetScale({ 50, 1, 50 });
	//GetGameObjectByName("ground").SetTexture(TEXTURES::GRID);

	CreateGameObject("solGen", MESHES::LOCAL_CUBE, TEXTURES::HERBE);
	GetGameObjectByName("solGen").SetTag(TAG_Floor);
	//GetGameObjectByName("solGen").SetPosition(POSITION_BASE);
	GetGameObjectByName("solGen").SetPosition({ 200,-2.5,100 });
	GetGameObjectByName("solGen").SetScale({ 400, 5, 200 });
	auto c = GetGameObjectByName("solGen").GetScale();
	GetGameObjectByName("solGen").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));

	CreateGameObject("field", MESHES::LOCAL_CUBE, TEXTURES::GRID);
	GetGameObjectByName("field").SetTag(TAG_Floor);
	GetGameObjectByName("field").SetPosition(POSITION_BASE);
	GetGameObjectByName("field").SetScale({ 100, 5, 50 });
	c = GetGameObjectByName("field").GetScale();
	GetGameObjectByName("field").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));

	CreateGameObject("Temple", MESHES::TEMPLE, TEXTURES::TEMPLE);
	GetGameObjectByName("Temple").SetTag(TAG_Floor);
	GetGameObjectByName("Temple").SetPosition({ 75,0,125 });
	//GetGameObjectByName("Temple").SetScale({ 100, 5, 100 });
	GetGameObjectByName("Temple").SetScale({ 0.75, 1, 0.75 });
	c = GetGameObjectByName("Temple").GetScale();
	GetGameObjectByName("Temple").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));

	CreateGameObject("Mountain", MESHES::LOCAL_CUBE, TEXTURES::CHAMP);
	GetGameObjectByName("Mountain").SetTag(TAG_Floor);
	GetGameObjectByName("Mountain").SetPosition({ 300,7,150 });
	GetGameObjectByName("Mountain").SetScale({ 200, 14, 100 });
	c = GetGameObjectByName("Mountain").GetScale();
	GetGameObjectByName("Mountain").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));

	//CreateGameObject("Mountain2", MESHES::LOCAL_CUBE, TEXTURES::CHAMP);
	//GetGameObjectByName("Mountain2").SetTag(TAG_Floor);
	//GetGameObjectByName("Mountain2").SetPosition({ 167.5, 2, 100 });
	//GetGameObjectByName("Mountain2").SetScale({ 65, 25, 20 });
	//c = GetGameObjectByName("Mountain2").GetScale();
	//GetGameObjectByName("Mountain2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));

	//CreateGameObject("Mountain3", MESHES::CAILLOUX4, TEXTURES::PIERRE);
	//GetGameObjectByName("Mountain3").SetTag(TAG_Floor);
	//GetGameObjectByName("Mountain3").SetPosition({ 125, 2, 100 });
	//GetGameObjectByName("Mountain3").SetScale({ 10, 12, 3 });
	//c = GetGameObjectByName("Mountain3").GetScale();
	//GetGameObjectByName("Mountain3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));

	{
		CreateGameObject("Road1", MESHES::LOCAL_CUBE, TEXTURES::CHAMP);
		GetGameObjectByName("Road1").SetTag(TAG_Floor);
		GetGameObjectByName("Road1").SetPosition({ 175, -2, 50 });
		GetGameObjectByName("Road1").SetScale({ 200, 5, 10 });
		c = GetGameObjectByName("Road1").GetScale();
		GetGameObjectByName("Road1").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));

		CreateGameObject("Road2", MESHES::LOCAL_CUBE, TEXTURES::CHAMP);
		GetGameObjectByName("Road2").SetTag(TAG_Floor);
		GetGameObjectByName("Road2").SetPosition({ 80, -2, 60 });
		GetGameObjectByName("Road2").SetScale({ 10, 5, 10 });
		c = GetGameObjectByName("Road2").GetScale();
		GetGameObjectByName("Road2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));

		CreateGameObject("Road3", MESHES::LOCAL_CUBE, TEXTURES::CHAMP);
		GetGameObjectByName("Road3").SetTag(TAG_Floor);
		GetGameObjectByName("Road3").SetPosition({ 75, -2, 80 });
		GetGameObjectByName("Road3").SetScale({ 75, 5, 30 });
		c = GetGameObjectByName("Road3").GetScale();
		GetGameObjectByName("Road3").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));
	}



	CreateGameObject("Pond", MESHES::LOCAL_CUBE, TEXTURES::EAU);
	GetGameObjectByName("Pond").SetTag(TAG_Floor);
	GetGameObjectByName("Pond").SetPosition({ 180, -2, 150 });
	GetGameObjectByName("Pond").SetScale({ 40, 5, 80 });
	c = GetGameObjectByName("Pond").GetScale();
	GetGameObjectByName("Pond").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));

	CreateGameObject("DownStream1", 2, TEXTURES::EAU);
	GetGameObjectByName("DownStream1").SetTag(TAG_Floor);
	GetGameObjectByName("DownStream1").SetPosition({ 155,-2,148 });
	GetGameObjectByName("DownStream1").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("DownStream1").SetScale({ 10,5,21 });
	c = GetGameObjectByName("DownStream1").GetScale();
	GetGameObjectByName("DownStream1").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));

	CreateGameObject("DownStream", MESHES::LOCAL_CUBE, TEXTURES::EAU);
	GetGameObjectByName("DownStream").SetTag(TAG_Floor);
	GetGameObjectByName("DownStream").SetPosition({ 140, -2, 80 });
	GetGameObjectByName("DownStream").SetScale({ 20, 5, 160 });
	c = GetGameObjectByName("DownStream").GetScale();
	GetGameObjectByName("DownStream").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));

	CreateGameObject("Waterfall", MESHES::LOCAL_CUBE, TEXTURES::EAU);
	GetGameObjectByName("Waterfall").SetTag(TAG_Floor);
	GetGameObjectByName("Waterfall").SetPosition({ 199.5, 7.5, 150 });
	GetGameObjectByName("Waterfall").SetScale({ 1, 15, 40 });
	c = GetGameObjectByName("Waterfall").GetScale();
	GetGameObjectByName("Waterfall").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));

	CreateGameObject("UpStream", MESHES::LOCAL_CUBE, TEXTURES::EAU);
	GetGameObjectByName("UpStream").SetTag(TAG_Floor);
	GetGameObjectByName("UpStream").SetPosition({ 220, 14, 150 });
	GetGameObjectByName("UpStream").SetScale({ 40, 2, 40 });
	c = GetGameObjectByName("UpStream").GetScale();
	GetGameObjectByName("UpStream").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));

	CreateGameObject("UpStream1", MESHES::LOCAL_CUBE, TEXTURES::EAU);
	GetGameObjectByName("UpStream1").SetTag(TAG_Floor);
	GetGameObjectByName("UpStream1").SetPosition({ 280, 14, 150 });
	GetGameObjectByName("UpStream1").SetScale({ 80, 2, 20 });
	c = GetGameObjectByName("UpStream1").GetScale();
	GetGameObjectByName("UpStream1").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));

	CreateGameObject("UpStream2", MESHES::LOCAL_CUBE, TEXTURES::EAU);
	GetGameObjectByName("UpStream2").SetTag(TAG_Floor);
	GetGameObjectByName("UpStream2").SetPosition({ 330, 14, 180 });
	GetGameObjectByName("UpStream2").SetScale({ 20, 2, 80 });
	c = GetGameObjectByName("UpStream2").GetScale();
	GetGameObjectByName("UpStream2").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({ c.x / 2, c.y / 2, c.z / 2 })));


	{
		CreateGameObject("GM0", 10, 13);
		GetGameObjectByName("GM0").SetPosition({ 196,2,175 });
		GetGameObjectByName("GM0").SetRotation({ 0,1,0,-1 });
		GetGameObjectByName("GM0").SetScale({ 6,4,4 });
		CreateGameObject("GM1", 10, 13);
		GetGameObjectByName("GM1").SetPosition({ 200,6,162 });
		GetGameObjectByName("GM1").SetRotation({ 0,-1,0,0 });
		GetGameObjectByName("GM1").SetScale({ 6,4,4 });
		CreateGameObject("GM2", 10, 13);
		GetGameObjectByName("GM2").SetPosition({ 197,0,162 });
		GetGameObjectByName("GM2").SetRotation({ 1,0,0,-1 });
		GetGameObjectByName("GM2").SetScale({ 6,4,4 });
		CreateGameObject("GM3", 10, 13);
		GetGameObjectByName("GM3").SetPosition({ 199,2,146 });
		GetGameObjectByName("GM3").SetRotation({ -1,1,0,0 });
		GetGameObjectByName("GM3").SetScale({ 6,4,4 });
		CreateGameObject("GM4", 10, 13);
		GetGameObjectByName("GM4").SetPosition({ 194,7,134 });
		GetGameObjectByName("GM4").SetRotation({ -1,0,1,0 });
		GetGameObjectByName("GM4").SetScale({ 6,4,4 });
		CreateGameObject("GM5", 10, 13);
		GetGameObjectByName("GM5").SetPosition({ 187,-1,137 });
		GetGameObjectByName("GM5").SetRotation({ -1,0,1,0 });
		GetGameObjectByName("GM5").SetScale({ 6,4,4 });
		CreateGameObject("GM8", 10, 13);
		GetGameObjectByName("GM8").SetPosition({ 185,-1,149 });
		GetGameObjectByName("GM8").SetRotation({ 0,0,1,0 });
		GetGameObjectByName("GM8").SetScale({ 6,4,4 });
		CreateGameObject("GM9", 10, 13);
		GetGameObjectByName("GM9").SetPosition({ 184,2,171 });
		GetGameObjectByName("GM9").SetRotation({ -1,0,0,0 });
		GetGameObjectByName("GM9").SetScale({ 6,4,4 });
		CreateGameObject("GM10", 10, 13);
		GetGameObjectByName("GM10").SetPosition({ 190,7,182 });
		GetGameObjectByName("GM10").SetRotation({ -1,0,0,0 });
		GetGameObjectByName("GM10").SetScale({ 6,4,4 });
		CreateGameObject("GM11", 10, 13);
		GetGameObjectByName("GM11").SetPosition({ 199,2,180 });
		GetGameObjectByName("GM11").SetRotation({ -1,0,0,-1 });
		GetGameObjectByName("GM11").SetScale({ 6,4,4 });
		CreateGameObject("GM12", 10, 13);
		GetGameObjectByName("GM12").SetPosition({ 202,9,176 });
		GetGameObjectByName("GM12").SetRotation({ 0,-1,0,1 });
		GetGameObjectByName("GM12").SetScale({ 6,4,4 });
		CreateGameObject("GM13", 9, 13);
		GetGameObjectByName("GM13").SetPosition({ 176,-4,126 });
		GetGameObjectByName("GM13").SetRotation({ 0,1,0,0 });
		GetGameObjectByName("GM13").SetScale({ 5,3,3 });
		CreateGameObject("GM14", 9, 13);
		GetGameObjectByName("GM14").SetPosition({ 165,-2,169 });
		GetGameObjectByName("GM14").SetRotation({ 0,1,0,0 });
		GetGameObjectByName("GM14").SetScale({ 3,1,2 });
		CreateGameObject("GM15", 9, 13);
		GetGameObjectByName("GM15").SetPosition({ 172,-3,184 });
		GetGameObjectByName("GM15").SetRotation({ 0,0,1,1 });
		GetGameObjectByName("GM15").SetScale({ 3,1,2 });
		CreateGameObject("GM16", 9, 13);
		GetGameObjectByName("GM16").SetPosition({ 175,-1,149 });
		GetGameObjectByName("GM16").SetRotation({ 0,-1,0,1 });
		GetGameObjectByName("GM16").SetScale({ 3,1,2 });
		CreateGameObject("GM18", 9, 13);
		GetGameObjectByName("GM18").SetPosition({ 137,-1,153 });
		GetGameObjectByName("GM18").SetRotation({ 0,0,0,1 });
		GetGameObjectByName("GM18").SetScale({ 1,1,2 });
		CreateGameObject("GM19", 9, 13);
		GetGameObjectByName("GM19").SetPosition({ 147,-1,131 });
		GetGameObjectByName("GM19").SetRotation({ 0,1,0,0 });
		GetGameObjectByName("GM19").SetScale({ 1,1,2 });
		CreateGameObject("GM21", 9, 13);
		GetGameObjectByName("GM21").SetPosition({ 135,-1,118 });
		GetGameObjectByName("GM21").SetRotation({ -1,1,0,0 });
		GetGameObjectByName("GM21").SetScale({ 1,1,2 });
		CreateGameObject("GM22", 9, 13);
		GetGameObjectByName("GM22").SetPosition({ 149,0,87 });
		GetGameObjectByName("GM22").SetRotation({ -1,1,0,0 });
		GetGameObjectByName("GM22").SetScale({ 1,1,2 });
		CreateGameObject("GM23", 9, 13);
		GetGameObjectByName("GM23").SetPosition({ 145,0,90 });
		GetGameObjectByName("GM23").SetRotation({ 0,1,0,0 });
		GetGameObjectByName("GM23").SetScale({ 1,1,2 });
		CreateGameObject("GM24", 9, 13);
		GetGameObjectByName("GM24").SetPosition({ 140,-1,88 });
		GetGameObjectByName("GM24").SetRotation({ 0,1,0,-1 });
		GetGameObjectByName("GM24").SetScale({ 1,1,2 });
		CreateGameObject("GM25", 9, 13);
		GetGameObjectByName("GM25").SetPosition({ 136,-3,70 });
		GetGameObjectByName("GM25").SetRotation({ 0,1,0,-1 });
		GetGameObjectByName("GM25").SetScale({ 1,1,2 });
		CreateGameObject("GM26", 9, 13);
		GetGameObjectByName("GM26").SetPosition({ 143,-3,17 });
		GetGameObjectByName("GM26").SetRotation({ 0,1,0,-1 });
		GetGameObjectByName("GM26").SetScale({ 1,1,2 });
		CreateGameObject("GM27", 9, 13);
		GetGameObjectByName("GM27").SetPosition({ 143,0,62 });
		GetGameObjectByName("GM27").SetRotation({ 0,0,-1,-1 });
		GetGameObjectByName("GM27").SetScale({ 1,1,2 });
		CreateGameObject("GM29", 9, 13);
		GetGameObjectByName("GM29").SetPosition({ 137,0,34 });
		GetGameObjectByName("GM29").SetRotation({ 0,0,-1,-1 });
		GetGameObjectByName("GM29").SetScale({ 1,1,2 });
		CreateGameObject("GM30", 9, 13);
		GetGameObjectByName("GM30").SetPosition({ 211,14,133 });
		GetGameObjectByName("GM30").SetRotation({ 0,0,-1,-1 });
		GetGameObjectByName("GM30").SetScale({ 1,1,2 });
		CreateGameObject("GM31", 9, 13);
		GetGameObjectByName("GM31").SetPosition({ 216,16,153 });
		GetGameObjectByName("GM31").SetRotation({ 0,0,-1,-1 });
		GetGameObjectByName("GM31").SetScale({ 1,1,2 });
		CreateGameObject("GM32", 9, 13);
		GetGameObjectByName("GM32").SetPosition({ 225,14,164 });
		GetGameObjectByName("GM32").SetRotation({ 0,0,-1,-1 });
		GetGameObjectByName("GM32").SetScale({ 1,1,2 });
		CreateGameObject("GM33", 9, 13);
		GetGameObjectByName("GM33").SetPosition({ 237,15,135 });
		GetGameObjectByName("GM33").SetRotation({ 0,1,0,0 });
		GetGameObjectByName("GM33").SetScale({ 1,1,2 });
		CreateGameObject("GM34", 9, 13);
		GetGameObjectByName("GM34").SetPosition({ 234,13,136 });
		GetGameObjectByName("GM34").SetRotation({ 0,0,0,-1 });
		GetGameObjectByName("GM34").SetScale({ 1,1,2 });
		CreateGameObject("GM35", 9, 13);
		GetGameObjectByName("GM35").SetPosition({ 210,16,174 });
		GetGameObjectByName("GM35").SetRotation({ 0,-1,1,0 });
		GetGameObjectByName("GM35").SetScale({ 3,3,4 });
		CreateGameObject("GM36", 9, 13);
		GetGameObjectByName("GM36").SetPosition({ 214,9,126 });
		GetGameObjectByName("GM36").SetRotation({ 1,-1,0,1 });
		GetGameObjectByName("GM36").SetScale({ 1,4,3 });
		CreateGameObject("GM37", 9, 13);
		GetGameObjectByName("GM37").SetPosition({ 212,11,143 });
		GetGameObjectByName("GM37").SetRotation({ 1,0,0,1 });
		GetGameObjectByName("GM37").SetScale({ 1,1,1 });

		CreateGameObject(" 1", 11, 13);
		GetGameObjectByName(" 1").SetPosition({ 206,15,179 });
		GetGameObjectByName(" 1").SetRotation({ 0.982319,-0.007949,0.182062,-0.042889 });
		GetGameObjectByName(" 1").SetScale({ 12,12,12 });
		CreateGameObject(" 2", 9, 13);
		GetGameObjectByName(" 2").SetPosition({ 212,18 ,196 });
		GetGameObjectByName(" 2").SetRotation({ -0.792598,0.023437,0.036788,0.608182 });
		GetGameObjectByName(" 2").SetScale({ 6 ,6 ,6 });
	}


	CreateGameObject("GM 0", 10, 13);
	GetGameObjectByName("GM 0").SetPosition({ 196,3,126 });
	GetGameObjectByName("GM 0").SetRotation({ -0.089285,0.598362,-0.324475,0.727123 });
	GetGameObjectByName("GM 0").SetScale({ 9,7,7 });
	CreateGameObject("GM 1", 10, 13);
	GetGameObjectByName("GM 1").SetPosition({ 193,0,171 });
	GetGameObjectByName("GM 1").SetRotation({ 0.015055,-0.497411,-0.049990,-0.865943 });
	GetGameObjectByName("GM 1").SetScale({ 12,3,7 });
	CreateGameObject("GM 2", 10, 13);
	GetGameObjectByName("GM 2").SetPosition({ 203,10,134 });
	GetGameObjectByName("GM 2").SetRotation({ 0.015055,-0.497411,-0.049990,-0.865943 });
	GetGameObjectByName("GM 2").SetScale({ 12,4,10 });
	CreateGameObject("GM 3", 10, 13);
	GetGameObjectByName("GM 3").SetPosition({ 343,12,147 });
	GetGameObjectByName("GM 3").SetRotation({ 0.036424,-0.516220,0.037403,0.854863 });
	GetGameObjectByName("GM 3").SetScale({ 12,4,10 });
	CreateGameObject("GM 4", 11, 13);
	GetGameObjectByName("GM 4").SetPosition({ 314,14,160 });
	GetGameObjectByName("GM 4").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("GM 4").SetScale({ 2,2,2 });
	CreateGameObject("GM 5", 11, 13);
	GetGameObjectByName("GM 5").SetPosition({ 292,14,145 });
	GetGameObjectByName("GM 5").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("GM 5").SetScale({ 2,2,2 });
	CreateGameObject("GM 6", 11, 13);
	GetGameObjectByName("GM 6").SetPosition({ 276,15,155 });
	GetGameObjectByName("GM 6").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("GM 6").SetScale({ 2,2,2 });
	CreateGameObject("GM 7", 11, 13);
	GetGameObjectByName("GM 7").SetPosition({ 248,14,141 });
	GetGameObjectByName("GM 7").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("GM 7").SetScale({ 4,4,4 });
	CreateGameObject("GM 8", 9, 13);
	GetGameObjectByName("GM 8").SetPosition({ 247,14,163 });
	GetGameObjectByName("GM 8").SetRotation({ 0.334401,-0.643537,-0.616420,-0.306696 });
	GetGameObjectByName("GM 8").SetScale({ 4,4,4 });
	CreateGameObject("GM 9", 9, 13);
	GetGameObjectByName("GM 9").SetPosition({ 240,12,140 });
	GetGameObjectByName("GM 9").SetRotation({ -0.715377,-0.119170,-0.101201,0.681024 });
	GetGameObjectByName("GM 9").SetScale({ 4,4,4 });
	CreateGameObject("GM 10", 9, 13);
	GetGameObjectByName("GM 10").SetPosition({ 216,12,130 });
	GetGameObjectByName("GM 10").SetRotation({ -0.579520,-0.436029,-0.404228,0.557346 });
	GetGameObjectByName("GM 10").SetScale({ 6,6,6 });
	CreateGameObject("GM 11", 9, 13);
	GetGameObjectByName("GM 11").SetPosition({ 209,11,126 });
	GetGameObjectByName("GM 11").SetRotation({ 0.001966,-0.967644,0.027343,0.250825 });
	GetGameObjectByName("GM 11").SetScale({ 7,3,5 });
	CreateGameObject("GM 12", 9, 13);
	GetGameObjectByName("GM 12").SetPosition({ 185,-3,136 });
	GetGameObjectByName("GM 12").SetRotation({ 0.001966,-0.967644,0.027343,0.250825 });
	GetGameObjectByName("GM 12").SetScale({ 7,1,5 });
	CreateGameObject("GM 13", 9, 13);
	GetGameObjectByName("GM 13").SetPosition({ 330,14,136 });
	GetGameObjectByName("GM 13").SetRotation({ 0.001966,-0.967644,0.027343,0.250825 });
	GetGameObjectByName("GM 13").SetScale({ 7,1,5 });
	CreateGameObject("GM 14", 9, 13);
	GetGameObjectByName("GM 14").SetPosition({ 318,10,166 });
	GetGameObjectByName("GM 14").SetRotation({ -0.029652,-0.798422,-0.001851,0.601365 });
	GetGameObjectByName("GM 14").SetScale({ 7,4,3 });


	CreateGameObject("Falaises 5", 35, 13);
	GetGameObjectByName("Falaises 5").SetPosition({ 393,6,99 });
	GetGameObjectByName("Falaises 5").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("Falaises 5").SetScale({ 15,15,15 });
	CreateGameObject("Falaises 30", 35, 13);
	GetGameObjectByName("Falaises 30").SetPosition({ 366,7,99 });
	GetGameObjectByName("Falaises 30").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("Falaises 30").SetScale({ 39,13,13 });
	CreateGameObject("Falaises 31", 35, 13);
	GetGameObjectByName("Falaises 31").SetPosition({ 316,7,99 });
	GetGameObjectByName("Falaises 31").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("Falaises 31").SetScale({ 61,13,13 });
	CreateGameObject("Falaises 32", 35, 13);
	GetGameObjectByName("Falaises 32").SetPosition({ 278,7,99 });
	GetGameObjectByName("Falaises 32").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("Falaises 32").SetScale({ 16,13,13 });
	CreateGameObject("Falaises 33", 35, 13);
	GetGameObjectByName("Falaises 33").SetPosition({ 256,7,100 });
	GetGameObjectByName("Falaises 33").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("Falaises 33").SetScale({ 28,13,13 });
	CreateGameObject("Falaises 34", 35, 13);
	GetGameObjectByName("Falaises 34").SetPosition({ 227,7,100 });
	GetGameObjectByName("Falaises 34").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("Falaises 34").SetScale({ 32,13,13 });
	CreateGameObject("Falaises 35", 35, 13);
	GetGameObjectByName("Falaises 35").SetPosition({ 206,7,100 });
	GetGameObjectByName("Falaises 35").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("Falaises 35").SetScale({ 12,13,13 });
	CreateGameObject("Home", 7, 18);
	GetGameObjectByName("Home").SetPosition({ 288,0,66 });								// MAISON
	GetGameObjectByName("Home").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("Home").SetScale({ 2,2,2 });
	CreateGameObject("Falaises 43", 2, 10);
	GetGameObjectByName("Falaises 43").SetPosition({ 339,0,66 });
	GetGameObjectByName("Falaises 43").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("Falaises 43").SetScale({ 61,2,12 });
	CreateGameObject("Falaises 50", 2, 10);
	GetGameObjectByName("Falaises 50").SetPosition({ 339,0,35 });
	GetGameObjectByName("Falaises 50").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("Falaises 50").SetScale({ 61,2,12 });
	CreateGameObject("Falaises 51", 2, 10);
	GetGameObjectByName("Falaises 51").SetPosition({ 339,0,50 });
	GetGameObjectByName("Falaises 51").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
	GetGameObjectByName("Falaises 51").SetScale({ 61,2,12 });

	CreateGameObject("Grosse Roche 0", 20, 13);
	GetGameObjectByName("Grosse Roche 0").SetPosition({ 182,-1,83 });
	GetGameObjectByName("Grosse Roche 0").SetRotation({ 0.000000,-0.942642,0.000000,-0.333807 });
	GetGameObjectByName("Grosse Roche 0").SetScale({ 7,19,6 });
	CreateGameObject("Grosse Roche 1", 20, 13);
	GetGameObjectByName("Grosse Roche 1").SetPosition({ 166,14,76 });
	GetGameObjectByName("Grosse Roche 1").SetRotation({ -0.046408,-0.103291,0.745790,0.656486 });
	GetGameObjectByName("Grosse Roche 1").SetScale({ 3,15,7 });
	CreateGameObject("Grosse Roche 2", 20, 13);
	GetGameObjectByName("Grosse Roche 2").SetPosition({ 212,-8,93 });
	GetGameObjectByName("Grosse Roche 2").SetRotation({ 0.056928,-0.391132,0.048629,0.917284 });
	GetGameObjectByName("Grosse Roche 2").SetScale({ 3,15,7 });
	CreateGameObject("Grosse Roche 3", 20, 13);
	GetGameObjectByName("Grosse Roche 3").SetPosition({ 133,7,77 });
	GetGameObjectByName("Grosse Roche 3").SetRotation({ -0.759371,0.591902,0.105220,-0.248869 });
	GetGameObjectByName("Grosse Roche 3").SetScale({ 2,8,6 });


	//if (auto go = FindGameObjectByName("Grosse Roche 4")) {
	//	go->SetPosition(...);
	//	go->SetRotation(...);
	//	go->SetScale(...);
	//}

	
		CreateGameObject("Enviro 0", 20, 13);
		GetGameObjectByName("Enviro 0").SetPosition({ 182,-1,83 });
		GetGameObjectByName("Enviro 0").SetRotation({ 0.000000,-0.942642,0.000000,-0.333807 });
		GetGameObjectByName("Enviro 0").SetScale({ 7,19,6 });
		CreateGameObject("Enviro 1", 20, 13);
		GetGameObjectByName("Enviro 1").SetPosition({ 166,14,76 });
		GetGameObjectByName("Enviro 1").SetRotation({ -0.046408,-0.103291,0.745790,0.656486 });
		GetGameObjectByName("Enviro 1").SetScale({ 3,15,7 });
		CreateGameObject("Enviro 2", 20, 13);
		GetGameObjectByName("Enviro 2").SetPosition({ 212,-8,93 });
		GetGameObjectByName("Enviro 2").SetRotation({ 0.056928,-0.391132,0.048629,0.917284 });
		GetGameObjectByName("Enviro 2").SetScale({ 3,15,7 });
		CreateGameObject("Enviro 7", 20, 13);
		GetGameObjectByName("Enviro 7").SetPosition({ 265,-109,253 });
		GetGameObjectByName("Enviro 7").SetRotation({ -0.084240,0.987563,0.132165,0.012428 });
		GetGameObjectByName("Enviro 7").SetScale({ 33,108,57 });
		CreateGameObject("Enviro 8", 20, 13);
		GetGameObjectByName("Enviro 8").SetPosition({ 1,-109,196 });
		GetGameObjectByName("Enviro 8").SetRotation({ -0.006872,0.849041,0.156578,0.504544 });
		GetGameObjectByName("Enviro 8").SetScale({ 33,108,57 });
		CreateGameObject("Enviro 9", 20, 13);
		GetGameObjectByName("Enviro 9").SetPosition({ 66,-178,-81 });
		GetGameObjectByName("Enviro 9").SetRotation({ -0.082276,0.979832,0.093736,0.156118 });
		GetGameObjectByName("Enviro 9").SetScale({ 33,99,36 });
		CreateGameObject("Enviro 13", 20, 13);
		GetGameObjectByName("Enviro 13").SetPosition({ 224,-5,13 });
		GetGameObjectByName("Enviro 13").SetRotation({ -0.020957,0.150974,-0.988302,-0.005197 });
		GetGameObjectByName("Enviro 13").SetScale({ 23,49,11 });
		CreateGameObject("Enviro 14", 20, 13);
		GetGameObjectByName("Enviro 14").SetPosition({ 316,-5,9 });
		GetGameObjectByName("Enviro 14").SetRotation({ -0.020957,0.150974,-0.988302,-0.005197 });
		GetGameObjectByName("Enviro 14").SetScale({ 23,49,11 });
		CreateGameObject("Enviro 16", 21, 7);
		GetGameObjectByName("Enviro 16").SetPosition({ 150,9,87 });
		GetGameObjectByName("Enviro 16").SetRotation({ 0.146554,-0.163324,-0.701534,0.678010 });
		GetGameObjectByName("Enviro 16").SetScale({ 10,26,7 });
		CreateGameObject("Enviro 17", 9, 7);
		GetGameObjectByName("Enviro 17").SetPosition({ 160,11,101 });
		GetGameObjectByName("Enviro 17").SetRotation({ 0.004797,0.591633,0.805110,0.041789 });
		GetGameObjectByName("Enviro 17").SetScale({ 6,8,8 });
		CreateGameObject("Enviro 20", 16, 14);
		GetGameObjectByName("Enviro 20").SetPosition({ 156,19,114 });
		GetGameObjectByName("Enviro 20").SetRotation({ -0.064022,0.639627,0.120610,-0.756460 });
		GetGameObjectByName("Enviro 20").SetScale({ 2,4,4 });

		{
			CreateGameObject("Tree 0", 15, 10);
			GetGameObjectByName("Tree 0").SetPosition({ 267,0,60 });
			GetGameObjectByName("Tree 0").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 0").SetScale({ 3,2,3 });
			CreateGameObject("Tree 1", 15, 10);
			GetGameObjectByName("Tree 1").SetPosition({ 253,0,83 });
			GetGameObjectByName("Tree 1").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 1").SetScale({ 3,2,3 });
			CreateGameObject("Tree 2", 15, 10);
			GetGameObjectByName("Tree 2").SetPosition({ 232,0,62 });
			GetGameObjectByName("Tree 2").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 2").SetScale({ 3,2,3 });
			CreateGameObject("Tree 3", 15, 10);
			GetGameObjectByName("Tree 3").SetPosition({ 206,0,66 });
			GetGameObjectByName("Tree 3").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 3").SetScale({ 3,2,3 });
			CreateGameObject("Tree 4", 15, 10);
			GetGameObjectByName("Tree 4").SetPosition({ 248,0,68 });
			GetGameObjectByName("Tree 4").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 4").SetScale({ 3,2,3 });
			CreateGameObject("Tree 5", 15, 10);
			GetGameObjectByName("Tree 5").SetPosition({ 277,0,82 });
			GetGameObjectByName("Tree 5").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 5").SetScale({ 3,2,3 });
			CreateGameObject("Tree 6", 15, 10);
			GetGameObjectByName("Tree 6").SetPosition({ 303,0,92 });
			GetGameObjectByName("Tree 6").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 6").SetScale({ 3,2,3 });
			CreateGameObject("Tree 7", 15, 10);
			GetGameObjectByName("Tree 7").SetPosition({ 315,0,80 });
			GetGameObjectByName("Tree 7").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 7").SetScale({ 3,2,3 });
			CreateGameObject("Tree 8", 15, 10);
			GetGameObjectByName("Tree 8").SetPosition({ 348,0,78 });
			GetGameObjectByName("Tree 8").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 8").SetScale({ 3,2,3 });
			CreateGameObject("Tree 9", 15, 10);
			GetGameObjectByName("Tree 9").SetPosition({ 372,0,86 });
			GetGameObjectByName("Tree 9").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 9").SetScale({ 3,2,3 });
			CreateGameObject("Tree 10", 15, 10);
			GetGameObjectByName("Tree 10").SetPosition({ 383,0,44 });
			GetGameObjectByName("Tree 10").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 10").SetScale({ 3,2,3 });
			CreateGameObject("Tree 11", 15, 10);
			GetGameObjectByName("Tree 11").SetPosition({ 390,0,11 });
			GetGameObjectByName("Tree 11").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 11").SetScale({ 3,2,3 });
			CreateGameObject("Tree 12", 15, 10);
			GetGameObjectByName("Tree 12").SetPosition({ 347,0,22 });
			GetGameObjectByName("Tree 12").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 12").SetScale({ 3,2,3 });
			CreateGameObject("Tree 13", 15, 10);
			GetGameObjectByName("Tree 13").SetPosition({ 328,0,6 });
			GetGameObjectByName("Tree 13").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 13").SetScale({ 3,2,3 });
			CreateGameObject("Tree 14", 15, 10);
			GetGameObjectByName("Tree 14").SetPosition({ 285,0,21 });
			GetGameObjectByName("Tree 14").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 14").SetScale({ 3,2,3 });
			CreateGameObject("Tree 15", 15, 10);
			GetGameObjectByName("Tree 15").SetPosition({ 251,0,16 });
			GetGameObjectByName("Tree 15").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 15").SetScale({ 3,2,3 });
			CreateGameObject("Tree 16", 15, 10);
			GetGameObjectByName("Tree 16").SetPosition({ 214,0,38 });
			GetGameObjectByName("Tree 16").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 16").SetScale({ 3,2,3 });
			CreateGameObject("Tree 17", 15, 10);
			GetGameObjectByName("Tree 17").SetPosition({ 176,0,26 });
			GetGameObjectByName("Tree 17").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 17").SetScale({ 3,2,3 });
			CreateGameObject("Tree 18", 15, 10);
			GetGameObjectByName("Tree 18").SetPosition({ 118,0,65 });
			GetGameObjectByName("Tree 18").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 18").SetScale({ 3,2,3 });
			CreateGameObject("Tree 19", 15, 10);
			GetGameObjectByName("Tree 19").SetPosition({ 102,0,30 });
			GetGameObjectByName("Tree 19").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 19").SetScale({ 3,2,3 });
			CreateGameObject("Tree 20", 15, 10);
			GetGameObjectByName("Tree 20").SetPosition({ 68,0,38 });
			GetGameObjectByName("Tree 20").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 20").SetScale({ 3,2,3 });
			CreateGameObject("Tree 21", 15, 10);
			GetGameObjectByName("Tree 21").SetPosition({ 63,0,60 });
			GetGameObjectByName("Tree 21").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 21").SetScale({ 3,2,3 });
			CreateGameObject("Tree 22", 15, 10);
			GetGameObjectByName("Tree 22").SetPosition({ 34,0,38 });
			GetGameObjectByName("Tree 22").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 22").SetScale({ 3,2,3 });
			CreateGameObject("Tree 23", 15, 10);
			GetGameObjectByName("Tree 23").SetPosition({ 17,0,68 });
			GetGameObjectByName("Tree 23").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 23").SetScale({ 3,2,3 });
			CreateGameObject("Tree 24", 15, 10);
			GetGameObjectByName("Tree 24").SetPosition({ 27,0,100 });
			GetGameObjectByName("Tree 24").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 24").SetScale({ 3,2,3 });
			CreateGameObject("Tree 25", 15, 10);
			GetGameObjectByName("Tree 25").SetPosition({ 70,0,176 });
			GetGameObjectByName("Tree 25").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 25").SetScale({ 3,2,3 });
			CreateGameObject("Tree 26", 15, 10);
			GetGameObjectByName("Tree 26").SetPosition({ 94,0,181 });
			GetGameObjectByName("Tree 26").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 26").SetScale({ 3,2,3 });
			CreateGameObject("Tree 27", 14, 10);
			GetGameObjectByName("Tree 27").SetPosition({ 217,-1,60 });
			GetGameObjectByName("Tree 27").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 27").SetScale({ 4,3,4 });
			CreateGameObject("Tree 28", 14, 10);
			GetGameObjectByName("Tree 28").SetPosition({ 197,-1,10 });
			GetGameObjectByName("Tree 28").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 28").SetScale({ 4,3,4 });
			CreateGameObject("Tree 29", 14, 10);
			GetGameObjectByName("Tree 29").SetPosition({ 391,-1,26 });
			GetGameObjectByName("Tree 29").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 29").SetScale({ 4,3,4 });
			CreateGameObject("Tree 30", 14, 10);
			GetGameObjectByName("Tree 30").SetPosition({ 257,-1,33 });
			GetGameObjectByName("Tree 30").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 30").SetScale({ 4,2,4 });
			CreateGameObject("Tree 31", 14, 10);
			GetGameObjectByName("Tree 31").SetPosition({ 265,-1,77 });
			GetGameObjectByName("Tree 31").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 31").SetScale({ 4,2,4 });
			CreateGameObject("Tree 32", 14, 10);
			GetGameObjectByName("Tree 32").SetPosition({ 339,-1,86 });
			GetGameObjectByName("Tree 32").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 32").SetScale({ 4,2,4 });
			CreateGameObject("Tree 33", 14, 10);
			GetGameObjectByName("Tree 33").SetPosition({ 388,-1,72 });
			GetGameObjectByName("Tree 33").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 33").SetScale({ 4,2,4 });
			CreateGameObject("Tree 34", 14, 10);
			GetGameObjectByName("Tree 34").SetPosition({ 307,-1,14 });
			GetGameObjectByName("Tree 34").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 34").SetScale({ 4,2,4 });
			CreateGameObject("Tree 35", 14, 10);
			GetGameObjectByName("Tree 35").SetPosition({ 230,-1,15 });
			GetGameObjectByName("Tree 35").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 35").SetScale({ 4,2,4 });
			CreateGameObject("Tree 36", 14, 10);
			GetGameObjectByName("Tree 36").SetPosition({ 55,-1,49 });
			GetGameObjectByName("Tree 36").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 36").SetScale({ 4,2,4 });
			CreateGameObject("Tree 37", 14, 10);
			GetGameObjectByName("Tree 37").SetPosition({ 8,-1,83 });
			GetGameObjectByName("Tree 37").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 37").SetScale({ 4,2,4 });
			CreateGameObject("Tree 38", 14, 10);
			GetGameObjectByName("Tree 38").SetPosition({ 25,-1,48 });
			GetGameObjectByName("Tree 38").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 38").SetScale({ 5,3,5 });
			CreateGameObject("Tree 39", 14, 10);
			GetGameObjectByName("Tree 39").SetPosition({ 24,-1,123 });
			GetGameObjectByName("Tree 39").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 39").SetScale({ 4,2,4 });
			CreateGameObject("Tree 40", 14, 10);
			GetGameObjectByName("Tree 40").SetPosition({ 80,-1,189 });
			GetGameObjectByName("Tree 40").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 40").SetScale({ 4,2,4 });
			CreateGameObject("Tree 41", 14, 10);
			GetGameObjectByName("Tree 41").SetPosition({ 129,-1,158 });
			GetGameObjectByName("Tree 41").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 41").SetScale({ 4,2,4 });
			CreateGameObject("Tree 42", 15, 10);
			GetGameObjectByName("Tree 42").SetPosition({ 190,0,66 });
			GetGameObjectByName("Tree 42").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 42").SetScale({ 3,1,3 });
			CreateGameObject("Tree 43", 15, 10);
			GetGameObjectByName("Tree 43").SetPosition({ 209,0,75 });
			GetGameObjectByName("Tree 43").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 43").SetScale({ 3,1,3 });
			CreateGameObject("Tree 44", 15, 10);
			GetGameObjectByName("Tree 44").SetPosition({ 237,0,64 });
			GetGameObjectByName("Tree 44").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 44").SetScale({ 3,1,3 });
			CreateGameObject("Tree 45", 15, 10);
			GetGameObjectByName("Tree 45").SetPosition({ 255,0,72 });
			GetGameObjectByName("Tree 45").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 45").SetScale({ 3,1,3 });
			CreateGameObject("Tree 46", 15, 10);
			GetGameObjectByName("Tree 46").SetPosition({ 266,0,87 });
			GetGameObjectByName("Tree 46").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 46").SetScale({ 3,1,3 });
			CreateGameObject("Tree 47", 15, 10);
			GetGameObjectByName("Tree 47").SetPosition({ 296,0,83 });
			GetGameObjectByName("Tree 47").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 47").SetScale({ 3,1,3 });
			CreateGameObject("Tree 48", 15, 10);
			GetGameObjectByName("Tree 48").SetPosition({ 318,0,89 });
			GetGameObjectByName("Tree 48").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 48").SetScale({ 3,1,3 });
			CreateGameObject("Tree 49", 15, 10);
			GetGameObjectByName("Tree 49").SetPosition({ 384,0,80 });
			GetGameObjectByName("Tree 49").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 49").SetScale({ 3,1,3 });
			CreateGameObject("Tree 50", 15, 10);
			GetGameObjectByName("Tree 50").SetPosition({ 381,0,33 });
			GetGameObjectByName("Tree 50").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 50").SetScale({ 3,1,3 });
			CreateGameObject("Tree 51", 15, 10);
			GetGameObjectByName("Tree 51").SetPosition({ 392,0,15 });
			GetGameObjectByName("Tree 51").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 51").SetScale({ 3,1,3 });
			CreateGameObject("Tree 52", 15, 10);
			GetGameObjectByName("Tree 52").SetPosition({ 352,0,18 });
			GetGameObjectByName("Tree 52").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 52").SetScale({ 3,1,3 });
			CreateGameObject("Tree 53", 15, 10);
			GetGameObjectByName("Tree 53").SetPosition({ 338,0,7 });
			GetGameObjectByName("Tree 53").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 53").SetScale({ 3,1,3 });
			CreateGameObject("Tree 54", 15, 10);
			GetGameObjectByName("Tree 54").SetPosition({ 316,0,15 });
			GetGameObjectByName("Tree 54").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 54").SetScale({ 3,1,3 });
			CreateGameObject("Tree 55", 15, 10);
			GetGameObjectByName("Tree 55").SetPosition({ 294,0,15 });
			GetGameObjectByName("Tree 55").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 55").SetScale({ 3,1,3 });
			CreateGameObject("Tree 56", 15, 10);
			GetGameObjectByName("Tree 56").SetPosition({ 268,0,15 });
			GetGameObjectByName("Tree 56").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 56").SetScale({ 3,1,3 });
			CreateGameObject("Tree 57", 15, 10);
			GetGameObjectByName("Tree 57").SetPosition({ 236,0,18 });
			GetGameObjectByName("Tree 57").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 57").SetScale({ 3,1,3 });
			CreateGameObject("Tree 58", 15, 10);
			GetGameObjectByName("Tree 58").SetPosition({ 223,0,26 });
			GetGameObjectByName("Tree 58").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 58").SetScale({ 3,1,3 });
			CreateGameObject("Tree 59", 15, 10);
			GetGameObjectByName("Tree 59").SetPosition({ 208,0,12 });
			GetGameObjectByName("Tree 59").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 59").SetScale({ 3,1,3 });
			CreateGameObject("Tree 60", 15, 10);
			GetGameObjectByName("Tree 60").SetPosition({ 185,0,10 });
			GetGameObjectByName("Tree 60").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 60").SetScale({ 3,1,3 });
			CreateGameObject("Tree 61", 15, 10);
			GetGameObjectByName("Tree 61").SetPosition({ 169,0,36 });
			GetGameObjectByName("Tree 61").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 61").SetScale({ 3,1,3 });
			CreateGameObject("Tree 62", 15, 10);
			GetGameObjectByName("Tree 62").SetPosition({ 103,0,61 });
			GetGameObjectByName("Tree 62").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 62").SetScale({ 3,1,3 });
			CreateGameObject("Tree 63", 15, 10);
			GetGameObjectByName("Tree 63").SetPosition({ 91,0,33 });
			GetGameObjectByName("Tree 63").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 63").SetScale({ 3,1,3 });
			CreateGameObject("Tree 64", 15, 10);
			GetGameObjectByName("Tree 64").SetPosition({ 59,0,33 });
			GetGameObjectByName("Tree 64").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 64").SetScale({ 3,1,3 });
			CreateGameObject("Tree 65", 15, 10);
			GetGameObjectByName("Tree 65").SetPosition({ 226,0,75 });
			GetGameObjectByName("Tree 65").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 65").SetScale({ 4,2,4 });
			CreateGameObject("Tree 66", 15, 10);
			GetGameObjectByName("Tree 66").SetPosition({ 239,0,92 });
			GetGameObjectByName("Tree 66").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 66").SetScale({ 4,2,4 });
			CreateGameObject("Tree 67", 15, 10);
			GetGameObjectByName("Tree 67").SetPosition({ 289,0,90 });
			GetGameObjectByName("Tree 67").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 67").SetScale({ 4,2,4 });
			CreateGameObject("Tree 68", 15, 10);
			GetGameObjectByName("Tree 68").SetPosition({ 330,0,84 });
			GetGameObjectByName("Tree 68").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 68").SetScale({ 4,2,4 });
			CreateGameObject("Tree 69", 15, 10);
			GetGameObjectByName("Tree 69").SetPosition({ 362,0,90 });
			GetGameObjectByName("Tree 69").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 69").SetScale({ 4,2,4 });
			CreateGameObject("Tree 70", 15, 10);
			GetGameObjectByName("Tree 70").SetPosition({ 380,0,54 });
			GetGameObjectByName("Tree 70").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 70").SetScale({ 4,2,4 });
			CreateGameObject("Tree 71", 15, 10);
			GetGameObjectByName("Tree 71").SetPosition({ 393,0,60 });
			GetGameObjectByName("Tree 71").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 71").SetScale({ 4,2,4 });
			CreateGameObject("Tree 72", 15, 10);
			GetGameObjectByName("Tree 72").SetPosition({ 373,0,13 });
			GetGameObjectByName("Tree 72").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 72").SetScale({ 4,2,4 });
			CreateGameObject("Tree 73", 15, 10);
			GetGameObjectByName("Tree 73").SetPosition({ 362,0,10 });
			GetGameObjectByName("Tree 73").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 73").SetScale({ 4,2,4 });
			CreateGameObject("Tree 75", 15, 10);
			GetGameObjectByName("Tree 75").SetPosition({ 307,0,3 });
			GetGameObjectByName("Tree 75").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 75").SetScale({ 4,2,4 });
			CreateGameObject("Tree 76", 15, 10);
			GetGameObjectByName("Tree 76").SetPosition({ 260,0,5 });
			GetGameObjectByName("Tree 76").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 76").SetScale({ 4,2,4 });
			CreateGameObject("Tree 77", 15, 10);
			GetGameObjectByName("Tree 77").SetPosition({ 240,0,5 });
			GetGameObjectByName("Tree 77").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 77").SetScale({ 4,2,4 });
			CreateGameObject("Tree 78", 15, 10);
			GetGameObjectByName("Tree 78").SetPosition({ 266,0,29 });
			GetGameObjectByName("Tree 78").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 78").SetScale({ 4,2,4 });
			CreateGameObject("Tree 79", 15, 10);
			GetGameObjectByName("Tree 79").SetPosition({ 228,0,33 });
			GetGameObjectByName("Tree 79").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 79").SetScale({ 4,2,4 });
			CreateGameObject("Tree 80", 15, 10);
			GetGameObjectByName("Tree 80").SetPosition({ 200,0,29 });
			GetGameObjectByName("Tree 80").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 80").SetScale({ 4,2,4 });
			CreateGameObject("Tree 81", 15, 10);
			GetGameObjectByName("Tree 81").SetPosition({ 189,0,38 });
			GetGameObjectByName("Tree 81").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 81").SetScale({ 4,2,4 });
			CreateGameObject("Tree 82", 15, 10);
			GetGameObjectByName("Tree 82").SetPosition({ 168,0,12 });
			GetGameObjectByName("Tree 82").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 82").SetScale({ 4,2,4 });
			CreateGameObject("Tree 83", 15, 10);
			GetGameObjectByName("Tree 83").SetPosition({ 281,0,8 });
			GetGameObjectByName("Tree 83").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 83").SetScale({ 4,2,4 });
			CreateGameObject("Tree 84", 15, 10);
			GetGameObjectByName("Tree 84").SetPosition({ 274,0,21 });
			GetGameObjectByName("Tree 84").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 84").SetScale({ 4,2,4 });
			CreateGameObject("Tree 85", 15, 10);
			GetGameObjectByName("Tree 85").SetPosition({ 333,0,20 });
			GetGameObjectByName("Tree 85").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 85").SetScale({ 4,2,4 });
			CreateGameObject("Tree 86", 15, 10);
			GetGameObjectByName("Tree 86").SetPosition({ 353,0,10 });
			GetGameObjectByName("Tree 86").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 86").SetScale({ 4,2,4 });
			CreateGameObject("Tree 87", 15, 10);
			GetGameObjectByName("Tree 87").SetPosition({ 392,0,48 });
			GetGameObjectByName("Tree 87").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 87").SetScale({ 4,2,4 });
			CreateGameObject("Tree 88", 15, 10);
			GetGameObjectByName("Tree 88").SetPosition({ 396,0,90 });
			GetGameObjectByName("Tree 88").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 88").SetScale({ 4,2,4 });
			CreateGameObject("Tree 89", 15, 10);
			GetGameObjectByName("Tree 89").SetPosition({ 122,0,23 });
			GetGameObjectByName("Tree 89").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 89").SetScale({ 4,2,4 });
			CreateGameObject("Tree 90", 15, 10);
			GetGameObjectByName("Tree 90").SetPosition({ 113,0,38 });
			GetGameObjectByName("Tree 90").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 90").SetScale({ 4,2,4 });
			CreateGameObject("Tree 91", 15, 10);
			GetGameObjectByName("Tree 91").SetPosition({ 35,0,30 });
			GetGameObjectByName("Tree 91").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 91").SetScale({ 4,2,4 });
			CreateGameObject("Tree 92", 15, 10);
			GetGameObjectByName("Tree 92").SetPosition({ 11,0,28 });
			GetGameObjectByName("Tree 92").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 92").SetScale({ 4,2,4 });
			CreateGameObject("Tree 93", 15, 10);
			GetGameObjectByName("Tree 93").SetPosition({ 33,0,77 });
			GetGameObjectByName("Tree 93").SetRotation({ 0.000000,0.000000,0.000000,1.000000 });
			GetGameObjectByName("Tree 93").SetScale({ 4,2,4 });
			CreateGameObject("Tree 94", 16, 10);
			GetGameObjectByName("Tree 94").SetPosition({ 158,0,160 });
			GetGameObjectByName("Tree 94").SetRotation({ 0.000000,0.216440,0.000000,0.976296 });
			GetGameObjectByName("Tree 94").SetScale({ 1,2,2 });
			CreateGameObject("Tree 95", 16, 10);
			GetGameObjectByName("Tree 95").SetPosition({ 126,0,4 });
			GetGameObjectByName("Tree 95").SetRotation({ 0.000000,0.216440,0.000000,0.976296 });
			GetGameObjectByName("Tree 95").SetScale({ 2,2,2 });
			CreateGameObject("Tree 96", 16, 10);
			GetGameObjectByName("Tree 96").SetPosition({ 122,0,120 });
			GetGameObjectByName("Tree 96").SetRotation({ 0.000000,0.430511,0.000000,0.902585 });
			GetGameObjectByName("Tree 96").SetScale({ 2,2,2 });
			CreateGameObject("Tree 97", 16, 10);
			GetGameObjectByName("Tree 97").SetPosition({ 227,14,171 });
			GetGameObjectByName("Tree 97").SetRotation({ 0.000000,0.994522,0.000000,0.104529 });
			GetGameObjectByName("Tree 97").SetScale({ 2,2,2 });
			CreateGameObject("Tree 98", 16, 10);
			GetGameObjectByName("Tree 98").SetPosition({ 341,14,132 });
			GetGameObjectByName("Tree 98").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 98").SetScale({ 3,3,3 });
			CreateGameObject("Tree 99", 14, 10);
			GetGameObjectByName("Tree 99").SetPosition({ 246,13,116 });
			GetGameObjectByName("Tree 99").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 99").SetScale({ 3,3,3 });
			CreateGameObject("Tree 100", 14, 10);
			GetGameObjectByName("Tree 100").SetPosition({ 279,13,133 });
			GetGameObjectByName("Tree 100").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 100").SetScale({ 3,3,3 });
			CreateGameObject("Tree 101", 14, 10);
			GetGameObjectByName("Tree 101").SetPosition({ 292,13,108 });
			GetGameObjectByName("Tree 101").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 101").SetScale({ 3,3,3 });
			CreateGameObject("Tree 102", 14, 10);
			GetGameObjectByName("Tree 102").SetPosition({ 313,13,111 });
			GetGameObjectByName("Tree 102").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 102").SetScale({ 3,3,3 });
			CreateGameObject("Tree 103", 14, 10);
			GetGameObjectByName("Tree 103").SetPosition({ 349,13,110 });
			GetGameObjectByName("Tree 103").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 103").SetScale({ 3,3,3 });
			CreateGameObject("Tree 104", 14, 10);
			GetGameObjectByName("Tree 104").SetPosition({ 379,13,109 });
			GetGameObjectByName("Tree 104").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 104").SetScale({ 3,3,3 });
			CreateGameObject("Tree 105", 14, 10);
			GetGameObjectByName("Tree 105").SetPosition({ 390,13,129 });
			GetGameObjectByName("Tree 105").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 105").SetScale({ 3,3,3 });
			CreateGameObject("Tree 106", 14, 10);
			GetGameObjectByName("Tree 106").SetPosition({ 369,13,125 });
			GetGameObjectByName("Tree 106").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 106").SetScale({ 3,3,3 });
			CreateGameObject("Tree 107", 14, 10);
			GetGameObjectByName("Tree 107").SetPosition({ 363,13,149 });
			GetGameObjectByName("Tree 107").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 107").SetScale({ 3,3,3 });
			CreateGameObject("Tree 108", 14, 10);
			GetGameObjectByName("Tree 108").SetPosition({ 378,13,168 });
			GetGameObjectByName("Tree 108").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 108").SetScale({ 3,3,3 });
			CreateGameObject("Tree 109", 14, 10);
			GetGameObjectByName("Tree 109").SetPosition({ 363,13,190 });
			GetGameObjectByName("Tree 109").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 109").SetScale({ 3,3,3 });
			CreateGameObject("Tree 110", 14, 10);
			GetGameObjectByName("Tree 110").SetPosition({ 346,13,178 });
			GetGameObjectByName("Tree 110").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 110").SetScale({ 3,3,3 });
			CreateGameObject("Tree 111", 14, 10);
			GetGameObjectByName("Tree 111").SetPosition({ 353,13,162 });
			GetGameObjectByName("Tree 111").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 111").SetScale({ 3,3,3 });
			CreateGameObject("Tree 112", 14, 10);
			GetGameObjectByName("Tree 112").SetPosition({ 299,13,184 });
			GetGameObjectByName("Tree 112").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 112").SetScale({ 3,3,3 });
			CreateGameObject("Tree 113", 14, 10);
			GetGameObjectByName("Tree 113").SetPosition({ 281,13,168 });
			GetGameObjectByName("Tree 113").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 113").SetScale({ 3,3,3 });
			CreateGameObject("Tree 114", 14, 10);
			GetGameObjectByName("Tree 114").SetPosition({ 252,13,170 });
			GetGameObjectByName("Tree 114").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 114").SetScale({ 3,3,3 });
			CreateGameObject("Tree 115", 14, 10);
			GetGameObjectByName("Tree 115").SetPosition({ 270,13,182 });
			GetGameObjectByName("Tree 115").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 115").SetScale({ 3,3,3 });
			CreateGameObject("Tree 116", 14, 10);
			GetGameObjectByName("Tree 116").SetPosition({ 257,13,193 });
			GetGameObjectByName("Tree 116").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 116").SetScale({ 3,3,3 });
			CreateGameObject("Tree 117", 14, 10);
			GetGameObjectByName("Tree 117").SetPosition({ 238,13,187 });
			GetGameObjectByName("Tree 117").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 117").SetScale({ 3,3,3 });
			CreateGameObject("Tree 118", 14, 10);
			GetGameObjectByName("Tree 118").SetPosition({ 265,13,106 });
			GetGameObjectByName("Tree 118").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 118").SetScale({ 4,3,4 });
			CreateGameObject("Tree 119", 14, 10);
			GetGameObjectByName("Tree 119").SetPosition({ 229,13,108 });
			GetGameObjectByName("Tree 119").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 119").SetScale({ 4,3,4 });
			CreateGameObject("Tree 120", 14, 10);
			GetGameObjectByName("Tree 120").SetPosition({ 383,13,147 });
			GetGameObjectByName("Tree 120").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 120").SetScale({ 4,3,4 });
			CreateGameObject("Tree 121", 14, 10);
			GetGameObjectByName("Tree 121").SetPosition({ 365,13,173 });
			GetGameObjectByName("Tree 121").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 121").SetScale({ 4,3,4 });
			CreateGameObject("Tree 122", 15, 10);
			GetGameObjectByName("Tree 122").SetPosition({ 333,13,111 });
			GetGameObjectByName("Tree 122").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 122").SetScale({ 4,3,4 });
			CreateGameObject("Tree 123", 15, 10);
			GetGameObjectByName("Tree 123").SetPosition({ 311,13,128 });
			GetGameObjectByName("Tree 123").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 123").SetScale({ 4,3,4 });
			CreateGameObject("Tree 124", 15, 10);
			GetGameObjectByName("Tree 124").SetPosition({ 296,13,121 });
			GetGameObjectByName("Tree 124").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 124").SetScale({ 4,3,4 });
			CreateGameObject("Tree 125", 15, 10);
			GetGameObjectByName("Tree 125").SetPosition({ 274,13,116 });
			GetGameObjectByName("Tree 125").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 125").SetScale({ 4,3,4 });
			CreateGameObject("Tree 126", 15, 10);
			GetGameObjectByName("Tree 126").SetPosition({ 260,13,186 });
			GetGameObjectByName("Tree 126").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 126").SetScale({ 4,3,4 });
			CreateGameObject("Tree 127", 15, 10);
			GetGameObjectByName("Tree 127").SetPosition({ 291,13,179 });
			GetGameObjectByName("Tree 127").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 127").SetScale({ 4,3,4 });
			CreateGameObject("Tree 129", 15, 10);
			GetGameObjectByName("Tree 129").SetPosition({ 223,13,195 });
			GetGameObjectByName("Tree 129").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 129").SetScale({ 4,3,4 });
			CreateGameObject("Tree 130", 15, 10);
			GetGameObjectByName("Tree 130").SetPosition({ 353,13,181 });
			GetGameObjectByName("Tree 130").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 130").SetScale({ 4,3,4 });
			CreateGameObject("Tree 131", 15, 10);
			GetGameObjectByName("Tree 131").SetPosition({ 387,13,170 });
			GetGameObjectByName("Tree 131").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 131").SetScale({ 4,3,4 });
			CreateGameObject("Tree 132", 15, 10);
			GetGameObjectByName("Tree 132").SetPosition({ 380,13,131 });
			GetGameObjectByName("Tree 132").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 132").SetScale({ 4,3,4 });
			CreateGameObject("Tree 133", 15, 10);
			GetGameObjectByName("Tree 133").SetPosition({ 389,13,106 });
			GetGameObjectByName("Tree 133").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 133").SetScale({ 4,3,4 });
			CreateGameObject("Tree 134", 15, 10);
			GetGameObjectByName("Tree 134").SetPosition({ 365,13,112 });
			GetGameObjectByName("Tree 134").SetRotation({ 0.000000,0.891007,0.000000,-0.453990 });
			GetGameObjectByName("Tree 134").SetScale({ 4,3,4 });
			CreateGameObject("Tree 135", 16, 10);
			GetGameObjectByName("Tree 135").SetPosition({ 159,21,85 });
			GetGameObjectByName("Tree 135").SetRotation({ -0.097665,0.929593,-0.037727,-0.353404 });
			GetGameObjectByName("Tree 135").SetScale({ 2,2,2 });
			CreateGameObject("Tree 136", 16, 10);
			GetGameObjectByName("Tree 136").SetPosition({ 183,45,93 });
			GetGameObjectByName("Tree 136").SetRotation({ -0.167166,0.913686,0.321412,0.184195 });
			GetGameObjectByName("Tree 136").SetScale({ 2,2,2 });
			CreateGameObject("Tree 137", 16, 10);
			GetGameObjectByName("Tree 137").SetPosition({ 193,5,179 });
			GetGameObjectByName("Tree 137").SetRotation({ -0.223416,0.418364,0.107304,0.873809 });
			GetGameObjectByName("Tree 137").SetScale({ 2,2,2 });
		}




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

	// Movements
	if (InputManager::GetKeyIsPressed(VK_SHIFT))
	{
		m_camSpeed = m_camRunSpeed;
		m_scaleSpeed = 5;
		m_zoomSensitivity = 10;
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
			m_placingHitbox.SetTexture(TEXTURES::GRID);
			m_placingHitbox.GetComponent<MeshComponent>()->alpha = 0.5;
			//m_placingHitbox.GetMesh().
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
					//auto& test = gm.GetPosition();
					//std::string cm_create = std::string("\nCreateGameObject(\"") + gm.GetName() + "\");";
					std::string cm_create = std::string("\nCreateGameObject(\"") + gm->GetName() + "\"" + "," + std::to_string(gm->GetMeshID()) + "," + std::to_string(gm->GetTexture()) + ");";
					std::string cm_position = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\").SetPosition({ " + RoundValueStr(gm->GetPosition().x) + "," + RoundValueStr(gm->GetPosition().y) + "," + RoundValueStr(gm->GetPosition().z) + " });";
					std::string cm_rotation = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\").SetRotation({ " + std::to_string(gm->GetRotation().x) + "," + std::to_string(gm->GetRotation().y) + "," + std::to_string(gm->GetRotation().z) + "," + std::to_string(gm->GetRotation().w) + " });";
					std::string cm_scale = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\").SetScale({ " + RoundValueStr(gm->GetScale().x) + "," + RoundValueStr(gm->GetScale().y) + "," + RoundValueStr(gm->GetScale().z) + " });";
					std::string cm_collider = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\").AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeAABB({" + FloatToStringNoTrailingZeros(gm->GetColliderX()) + ", " + FloatToStringNoTrailingZeros(gm->GetColliderY()) + ", " + FloatToStringNoTrailingZeros(gm->GetColliderZ()) + " })));";

					/*	std::string cm_create = std::string("\nCreateGameObject(\"") + gm->GetName() + "\"" + "," + std::to_string(gm->GetMesh()) + "," + std::to_string(gm->GetTexture()) + ");";
						std::string cm_position = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\").SetPosition({ " + std::to_string(gm->GetPosition().x) + "," + std::to_string(gm->GetPosition().y) + "," + std::to_string(gm->GetPosition().z) + " });";
						std::string cm_rotation = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\").SetRotation({ " + std::to_string(gm->GetRotation().x) + "," + std::to_string(gm->GetRotation().y) + "," + std::to_string(gm->GetRotation().z) + "," + std::to_string(gm->GetRotation().w) + " });";
						std::string cm_scale = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\").SetScale({ " + std::to_string(gm->GetScale().x) + "," + std::to_string(gm->GetScale().y) + "," + std::to_string(gm->GetScale().z) + " });";*/

					OutputDebugStringA(cm_create.c_str());
					OutputDebugStringA(cm_position.c_str());
					OutputDebugStringA(cm_rotation.c_str());
					OutputDebugStringA(cm_scale.c_str());
					if (gm->GetColliderX() > 0)
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
			GetGameObjectByName(gmName).SetPosition({ posCamera });
			GetGameObjectByName(gmName).SetRotation({ rotCamera });
			GetGameObjectByName(gmName).SetScale({ scaleCamera });
			GetGameObjectByName(gmName).SetTag(TAG_Object);

			// hitbox
			GetGameObjectByName(gmName).SetColliderX(m_placingHitbox.GetComponent<TransformComponent>()->scale.x / 2);
			GetGameObjectByName(gmName).SetColliderY(m_placingHitbox.GetComponent<TransformComponent>()->scale.y / 2);
			GetGameObjectByName(gmName).SetColliderZ(m_placingHitbox.GetComponent<TransformComponent>()->scale.z / 2);

			std::string msg = "\nAdded " + gmName + " At[ X: " + RoundValueStr(GetGameObjectByName(gmName).GetPosition().x) + " Y: " + RoundValueStr(GetGameObjectByName(gmName).GetPosition().y) + " Z: " + RoundValueStr(GetGameObjectByName(gmName).GetPosition().z);
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