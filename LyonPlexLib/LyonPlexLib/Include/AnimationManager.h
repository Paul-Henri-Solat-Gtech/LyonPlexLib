#pragma once
class AnimationManager
{
public:
	AnimationManager();
	void Init(float animationSpeed, GameObject* gmToAnimate);
	void Update(float deltatime);

	void CreateAnimation();
	void AnimationSystem();
	
	void AddFrame(TEXTURES::TEXTURES newFrameTexture) { m_textureList.push_back(newFrameTexture); };
	void SetGameobjectToAnimate(GameObject* gmToAnimate) { m_gameObjectToAnimate = gmToAnimate; };

private:
	TEXTURES::TEXTURES m_actualTexture;

	std::vector<TEXTURES::TEXTURES> m_textureList;

	GameObject* m_gameObjectToAnimate;

	float m_frameCooldown, m_frameOriginalCooldown;
	int m_nextIdFrame;
};

