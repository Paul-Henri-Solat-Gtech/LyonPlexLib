#include "pch.h"
#include "HealingRock.h"

HealingRock::HealingRock(Scene* scene, GameObject& playerGm, XMFLOAT3 pos, float lifetime) : GameObject(), m_playerGm(playerGm), m_lifetime(lifetime)
{
	mp_scene = scene;

	InitGameObj(mp_scene->GetEcsManager(), mp_scene);
	SetMesh(MESHES::LOCAL_SQUARE);
	SetTexture(TEXTURES::HEALROCK);
	AddComponent<Tag_HealingRock>(new Tag_HealingRock());
	SetTag(Tag::TAG_HealingRock);
	SetPosition(pos);
	SetScale({ 1,1,1 });
	auto rockScale = GetScale();
	AddComponent<CollisionComponent>(new CollisionComponent(CollisionComponent::MakeOBB({ rockScale.x / 2, rockScale.y / 2, rockScale.z / 2 })));
}

void HealingRock::OnUpdate(float deltatime)
{
	if (m_lifetime <= 0)
	{
		Destroy();
		//return;
	}
	else
	{
		//LookAt(m_playerGm);

		m_lifetime -= 1 * deltatime;
	}
}

void HealingRock::Destroy()
{
	mp_scene->DestroyGameObject(*this);
}
