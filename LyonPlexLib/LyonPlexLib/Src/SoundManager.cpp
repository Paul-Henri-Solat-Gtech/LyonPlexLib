#include "pch.h"
#include "SoundManager.h"

//bool SoundManager::Init()
//{
//    //verifie engine->IsAudioDevicePresent() ou Reset si necessaire
//    audioEngine = std::make_unique<AudioEngine>();
//
//    // Charger un effet sonore (WAV)
//    soundEffect = std::make_unique<SoundEffect>(audioEngine.get(), L"Explosion.wav");
//
//    // Créer une instance
//    soundInst = soundEffect->CreateInstance();
//
//
//	return true;
//}
//
//void SoundManager::CreateSound(const std::string& soundName, const std::wstring& soundPath)
//{
//    // Charger un effet sonore (WAV)
//    SavedSound newSound;
//    newSound.soundName = soundName;
//    newSound.sound = std::make_unique<SoundEffect>(audioEngine.get(), soundPath); // L"soundPath.wav"
//
//    SoundsList.push_back(newSound);
//}
