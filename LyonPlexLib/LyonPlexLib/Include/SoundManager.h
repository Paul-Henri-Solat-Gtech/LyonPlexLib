#pragma once

struct SavedSound{
	std::string soundName;
	//std::unique_ptr<SoundEffect> sound;
};

class SoundManager
{
public:
	bool Init();

	//void CreateSound(const std::string& soundName, const std::wstring& soundPath);
private:

	//std::unique_ptr<AudioEngine> audioEngine;
	//std::unique_ptr<SoundEffect> soundEffect;
	//std::unique_ptr<SoundEffectInstance> soundInst;

	//std::vector<SavedSound> SoundsList;
};

