#pragma once
class AnimationManager
{
public:
	AnimationManager();
	void Init(float animationSpeed, GameObject* gmToAnimate);
	void Start(float deltatime);
	void Loop(float deltatime);

	void AnimationSequence(float deltatime);
	void AnimationSystem();
	
	void AddFrame(TEXTURES::TEXTURES newFrameTexture) { m_textureList.push_back(newFrameTexture); };
	void SetGameobjectToAnimate(GameObject* gmToAnimate) { m_gameObjectToAnimate = gmToAnimate; };

	bool GetAnimationHisFinished() { return m_animationHisFinished; };

private:
	TEXTURES::TEXTURES m_actualTexture;

	std::vector<TEXTURES::TEXTURES> m_textureList;

	GameObject* m_gameObjectToAnimate;

	float m_frameCooldown, m_frameOriginalCooldown;
	int m_nextIdFrame;
	bool m_animationHisFinished;
};

