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

	{
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

	// ChangeScene
	if (InputManager::GetKeyIsReleased('A'))
	{
		ChangeScene("MainMenuScene");
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
		uint32_t meshID = m_placingModule.GetMesh();
		uint32_t textureID = m_placingModule.GetTexture();

		std::string gmName = "Falaises " + std::to_string(m_newIdGM);

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
				std::string cm_create = std::string("\nCreateGameObject(\"") + gm->GetName() + "\"" + "," + std::to_string(gm->GetMesh()) + "," + std::to_string(gm->GetTexture()) + ");";
				std::string cm_position = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\").SetPosition({ " + RoundValueStr(gm->GetPosition().x) + "," + RoundValueStr(gm->GetPosition().y) + "," + RoundValueStr(gm->GetPosition().z) + " });";
				std::string cm_rotation = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\").SetRotation({ " + std::to_string(gm->GetRotation().x) + "," + std::to_string(gm->GetRotation().y) + "," + std::to_string(gm->GetRotation().z) + "," + std::to_string(gm->GetRotation().w) + " });";
				std::string cm_scale = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\").SetScale({ " + RoundValueStr(gm->GetScale().x) + "," + RoundValueStr(gm->GetScale().y) + "," + RoundValueStr(gm->GetScale().z) + " });";

				/*	std::string cm_create = std::string("\nCreateGameObject(\"") + gm->GetName() + "\"" + "," + std::to_string(gm->GetMesh()) + "," + std::to_string(gm->GetTexture()) + ");";
					std::string cm_position = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\").SetPosition({ " + std::to_string(gm->GetPosition().x) + "," + std::to_string(gm->GetPosition().y) + "," + std::to_string(gm->GetPosition().z) + " });";
					std::string cm_rotation = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\").SetRotation({ " + std::to_string(gm->GetRotation().x) + "," + std::to_string(gm->GetRotation().y) + "," + std::to_string(gm->GetRotation().z) + "," + std::to_string(gm->GetRotation().w) + " });";
					std::string cm_scale = std::string("\nGetGameObjectByName(\"") + gm->GetName() + "\").SetScale({ " + std::to_string(gm->GetScale().x) + "," + std::to_string(gm->GetScale().y) + "," + std::to_string(gm->GetScale().z) + " });";*/

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

	/*if (InputManager::GetKeyIsReleased('3'))
	{
		m_placingModule.SetTexture(2);
	}*/
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