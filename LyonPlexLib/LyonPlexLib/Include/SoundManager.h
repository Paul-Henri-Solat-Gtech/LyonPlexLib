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
	void PlaySoundPlex(std::string soundName);
	void PlayMusicPlex(std::string musicName);
	void StopMusic();

	void Release();

private:
	// Moteur audio
	std::unique_ptr<DirectX::AudioEngine> m_audioEngine;

	// Liste des effets chargés (inclut aussi la musique)
	std::vector<SavedSound> m_soundsList;

	// Instances d'effets en cours de lecture (pour éviter destruction immédiate)
	std::vector<std::unique_ptr<DirectX::SoundEffectInstance>> m_activeSoundInstances;

	// Instance de musique en cours (bouclée)
	std::unique_ptr<DirectX::SoundEffectInstance> m_musicInstance;

	//// General Audio
	//std::unique_ptr<AudioEngine> m_audioEngine;
	//std::vector<SavedSound> m_soundsList;
	//std::vector<SoundEffectInstance> m_activeInstance;

	//// Sound
	//std::unique_ptr<SoundEffect> m_soundEffect;
	//std::unique_ptr<SoundEffectInstance> m_soundInst;

	//// Music
	//std::vector<std::unique_ptr<DirectX::SoundEffectInstance>> m_activeInstances;
	//std::unique_ptr<DirectX::SoundEffectInstance> m_musicInst;

};

