#pragma once

#include "Audio.h"
//using namespace DirectX;

struct SavedSound{
	std::string soundName;
	std::unique_ptr<SoundEffect> sound;
};

class SoundManager
{
public:
	bool Init();

	void CreateSound(const std::string& soundName, const std::wstring& soundPath);
	void PlaySoundPlex(std::string soundName);

	void Release();

private:
	std::unique_ptr<AudioEngine> m_audioEngine;
	std::unique_ptr<SoundEffect> m_soundEffect;
	std::unique_ptr<SoundEffectInstance> m_soundInst;

	std::vector<SavedSound> m_soundsList;
	std::vector<SoundEffectInstance> m_activeInstance;
};

