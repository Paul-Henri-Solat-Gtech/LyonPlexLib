#include "pch.h"
#include "SoundManager.h"

bool SoundManager::Init()
{
    //verifie engine->IsAudioDevicePresent() ou Reset si necessaire
    m_audioEngine = std::make_unique<AudioEngine>();

    if (!m_audioEngine->IsAudioDevicePresent()) 
    {
        return false;
    }

	return true;
}

void SoundManager::CreateSound(const std::string& soundName, const std::wstring& soundPath)
{
    // 1) Vérifier que le fichier existe
    if (!std::filesystem::exists(soundPath)) 
    {
        throw std::runtime_error("Sound file not found: " + std::string(soundPath.begin(), soundPath.end()));
    }
       
    // 2) Convertir en chemin pleinement qualifié (optionnel mais utile pour debug)
    DWORD len = GetFullPathNameW(soundPath.c_str(), 0, nullptr, nullptr);
    std::wstring fullPath(len, L'\0');
    GetFullPathNameW(soundPath.c_str(), len, fullPath.data(), nullptr);

    // 3) Charger le sond
    try
    {
        SavedSound newSound;
        newSound.soundName = soundName;
        newSound.sound = std::make_unique<DirectX::SoundEffect>(m_audioEngine.get(),fullPath.c_str());
        m_soundsList.push_back(std::move(newSound));
    }
    catch (const std::exception& ex)
    {
        // Recupere l’erreur DirectXTK
        throw std::runtime_error("Failed to load sound '" + soundName + "': " + ex.what());
    }
}

void SoundManager::PlaySoundPlex(std::string soundName)
{
    for (auto& savedSound : m_soundsList) 
    {
        if (savedSound.soundName == soundName)
        {
            // Cree une instance et la joue immediatement
            auto newSoundInstance = savedSound.sound->CreateInstance();
            newSoundInstance->Play();
            m_activeSoundInstances.push_back(std::move(newSoundInstance));
            
            std::string msg = std::string("PlayingSound: ") + soundName;
            OutputDebugStringA(msg.c_str());
            break;
        }
    }
}

void SoundManager::PlayMusicPlex(std::string musicName)
{
    // Stop la musique en cours
    StopMusic();

    for (auto& snd : m_soundsList)
    {
        if (snd.soundName == musicName)
        {
            auto inst = snd.sound->CreateInstance();
            inst->Play(true); // true = loop
            m_musicInstance = std::move(inst);
            break;
        }
    }
}

void SoundManager::StopMusic()
{
    if (m_musicInstance)
    {
        m_musicInstance->Stop();
        m_musicInstance.reset();
    }
}


void SoundManager::Release()
{
    // 1) Arrêter et libérer l'instance de lecture courante
    // Stoppe tous les effets
    for (auto& inst : m_activeSoundInstances) 
    {
        inst->Stop();
    }
    m_activeSoundInstances.clear();

    // Stoppe la musique
    if (m_musicInstance) 
    {
        m_musicInstance->Stop();
    }
    m_musicInstance.reset();

    // 2) Vider la liste des SoundEffect
    m_soundsList.clear();  // détruit tous les SoundEffect

    // 3) Détruire l’AudioEngine
    m_audioEngine.reset(); // le destructeur d’AudioEngine fera le shutdown interne
}