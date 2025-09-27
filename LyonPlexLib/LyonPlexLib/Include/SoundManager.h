#pragma once

#include "Audio.h"
//using namespace DirectX;

struct SavedSound
{
	std::string soundName;
	std::unique_ptr<SoundEffect> sound;
};

class SoundManager
{
public:
	bool Init();

	void CreateSound(const std::string& soundName, const std::wstring& soundPath);
	DirectX::SoundEffectInstance* PlaySoundPlex(std::string soundName, bool loop = false);

	void PlayMusicPlex(std::string musicName);
	void StopMusic();

	void SetVolume(std::string musicName, float volume);
	void SetMasterVolume(float volume);

	DirectX::SoundEffectInstance* GetLastInstance(const std::string& soundName) const;

	void Release();

	~SoundManager() { m_alive = false; }
	bool IsAlive() const { return m_alive; }

private:
	// Moteur audio
	std::unique_ptr<DirectX::AudioEngine> m_audioEngine;

	std::vector<SavedSound> m_soundsList;

	// Instances d'effets en cours de lecture (pour éviter destruction immédiate)
	std::vector<std::unique_ptr<DirectX::SoundEffectInstance>> m_activeSoundInstances;

	// Instance de musique en cours
	std::unique_ptr<DirectX::SoundEffectInstance> m_musicInstance;
	std::string m_musicName;

	// instances regroupees par nom
	std::unordered_map<std::string, std::vector<DirectX::SoundEffectInstance*>> m_instancesByName;

	// Volume par defaut
	std::unordered_map<std::string, float> m_defaultVolumes;

	bool m_alive = true;

};

