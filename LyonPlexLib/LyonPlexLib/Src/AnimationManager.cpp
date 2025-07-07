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
    m_attackHisFinished = false;
}

void AnimationManager::Start(float deltatime)
{
    m_actualTexture = m_textureList[m_nextIdFrame];
    m_gameObjectToAnimate->SetTexture(m_actualTexture);
    OutputDebugStringA(("\nFrame " + std::to_string(m_nextIdFrame) + "\n").c_str());

    while (m_frameCooldown > 0)
    {
        m_frameCooldown -= 1 * deltatime;
    }

    // 4) set next id frame
    m_nextIdFrame++;

    if (m_nextIdFrame <= m_textureList.size() +1 )
    {
        Start(deltatime);
    }
    else
    {
        m_attackHisFinished = true;
    }
}

void AnimationManager::AnimationSequence(float deltatime)
{
    if (m_textureList.empty() || !m_gameObjectToAnimate)
        return;

    // Decrease cooldown
    m_frameCooldown -= deltatime;

    if (m_frameCooldown <= 0.0f)
    {
        // Advance frame index safely
        m_nextIdFrame = (m_nextIdFrame + 1) % m_textureList.size();
        m_frameCooldown = m_frameOriginalCooldown;

        // Apply new texture
        const auto& textureId = m_textureList[m_nextIdFrame];
        m_gameObjectToAnimate->SetTexture(textureId);
        OutputDebugStringA(("Frame " + std::to_string(m_nextIdFrame) + "\n").c_str());
    }
}

void AnimationManager::Loop(float deltatime)
{
	m_frameCooldown -= 1 * deltatime;
	AnimationSystem();
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
