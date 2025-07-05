#include "pch.h"
#include "AnimationManager.h"

AnimationManager::AnimationManager() : m_gameObjectToAnimate(nullptr), m_frameCooldown(0.0f), m_frameOriginalCooldown(0.0f), m_nextIdFrame(0)
{
}

void AnimationManager::Init(float animationSpeed, GameObject* gmToAnimate)
{
	m_nextIdFrame = 0;
	m_frameOriginalCooldown = animationSpeed;
	m_frameCooldown = m_frameOriginalCooldown;
	m_gameObjectToAnimate = gmToAnimate;
}

void AnimationManager::Update(float deltatime)
{
	m_frameCooldown -= 1 * deltatime;
	AnimationSystem();
}

void AnimationManager::CreateAnimation()
{

}

void AnimationManager::AnimationSystem()
{
    if (m_frameCooldown > 0) 
    {
        return;
    }


    // 1) reset cooldown
    m_frameCooldown = m_frameOriginalCooldown;

    // 2) reset frame 0
    if (m_nextIdFrame >= m_textureList.size()) 
    {
        m_nextIdFrame = 0;
    }

    // 3) set frame
    m_actualTexture = m_textureList[m_nextIdFrame];
    m_gameObjectToAnimate->SetTexture(m_actualTexture);
    OutputDebugStringA(("\nFrame " + std::to_string(m_nextIdFrame) + "\n").c_str());

    // 4) set next id frame
    m_nextIdFrame++;
}
