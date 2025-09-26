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
    if (m_soundsList.empty()) return;

    for (auto& savedSound : m_soundsList)
    {
        if (!savedSound.sound) continue;
        if (savedSound.soundName == soundName)
        {
            auto inst = savedSound.sound->CreateInstance();
            if (!inst) break;
            inst->Play();
            m_instancesByName[soundName].push_back(inst.get());
            m_activeSoundInstances.push_back(std::move(inst));

           // OutputDebugStringA((std::string("PlayingSound: ") + soundName + "\n").c_str());
            break;
        }
    }
}

void SoundManager::PlayMusicPlex(std::string musicName)
{
    // Stop la musique en cours
    //StopMusic();

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

void SoundManager::SetVolume(std::string soundName, float volume)
{
    volume = std::clamp(volume, 0.0f, 1.0f);

    auto it = m_instancesByName.find(soundName);
    if (it != m_instancesByName.end())
    {
        for (auto* inst : it->second)
        {
            if (inst) inst->SetVolume(volume);
        }
    }
}

void SoundManager::SetMasterVolume(float volume)
{
    if (m_audioEngine) 
    {
        m_audioEngine->SetMasterVolume(std::clamp(volume, 0.0f, 1.0f));
    }
}

void SoundManager::Release()
{
    for (auto& inst : m_activeSoundInstances)
    {
        if (inst) inst->Stop();
    }
    m_activeSoundInstances.clear();
    m_instancesByName.clear();

    if (m_musicInstance)
    {
        m_musicInstance->Stop();
    }
    m_musicInstance.reset();

    m_soundsList.clear();
    m_audioEngine.reset();
}