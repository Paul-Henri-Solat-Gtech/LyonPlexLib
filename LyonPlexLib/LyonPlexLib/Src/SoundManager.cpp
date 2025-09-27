#include "pch.h"
#include "SoundManager.h"

// normalize volume: accept either 0..1 or percent (eg 50.f => 0.5f)
static float NormalizeVolume(float v)
{
    if (v > 1.0f) return std::clamp(v / 100.0f, 0.0f, 1.0f);
    return std::clamp(v, 0.0f, 1.0f);
}

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

        // if no default volume set, assume 1.0f
        if (m_defaultVolumes.find(soundName) == m_defaultVolumes.end())
            m_defaultVolumes[soundName] = 1.0f;
    }
    catch (const std::exception& ex)
    {
        // Recupere l’erreur DirectXTK
        throw std::runtime_error("Failed to load sound '" + soundName + "': " + ex.what());
    }
}

DirectX::SoundEffectInstance* SoundManager::PlaySoundPlex(std::string soundName, bool loop)
{
    if (m_soundsList.empty()) return nullptr;

    for (auto& savedSound : m_soundsList)
    {
        if (!savedSound.sound) continue;
        if (savedSound.soundName == soundName)
        {
            auto inst = savedSound.sound->CreateInstance();
            if (!inst) break;

            // apply default volume if present
            auto itVol = m_defaultVolumes.find(soundName);
            if (itVol != m_defaultVolumes.end())
            {
                inst->SetVolume(itVol->second);
            }

            inst->Play(loop);
            DirectX::SoundEffectInstance* rawPtr = inst.get();

            // stocke pointer non owning par nom
            m_instancesByName[soundName].push_back(rawPtr);
            // garde propriete
            m_activeSoundInstances.push_back(std::move(inst));

            return rawPtr;
        }
    }

    return nullptr;
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
            if (!inst) break;

            // apply default volume if present
            auto itVol = m_defaultVolumes.find(musicName);
            if (itVol != m_defaultVolumes.end())
            {
                inst->SetVolume(itVol->second);
            }

            inst->Play(true); // loop pour musique
            m_musicInstance = std::move(inst);
            m_musicName = musicName;
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
    m_musicName.clear();
}

void SoundManager::SetVolume(std::string soundName, float volume)
{
    float v = NormalizeVolume(volume);

    // store as default for future instances
    m_defaultVolumes[soundName] = v;

    // apply to music instance if matches
    if (!m_musicName.empty() && soundName == m_musicName)
    {
        if (m_musicInstance)
            m_musicInstance->SetVolume(v);
    }

    // apply to current instances (if still valid)
    auto soundInstance = m_instancesByName.find(soundName);
    if (soundInstance != m_instancesByName.end())
    {
        auto& vec = soundInstance->second;
        std::vector<DirectX::SoundEffectInstance*> alivePtrs;
        alivePtrs.reserve(vec.size());

        for (auto* inst : vec)
        {
            if (inst)
            {
                inst->SetVolume(v);
                alivePtrs.push_back(inst);
            }
        }
        vec = std::move(alivePtrs);
    }
}

void SoundManager::SetMasterVolume(float volume)
{
    if (m_audioEngine) 
    {
        m_audioEngine->SetMasterVolume(std::clamp(volume, 0.0f, 1.0f));
    }
}

DirectX::SoundEffectInstance* SoundManager::GetLastInstance(const std::string& soundName) const
{
    auto it = m_instancesByName.find(soundName);
    if (it == m_instancesByName.end()) return nullptr;
    const auto& vec = it->second;
    if (vec.empty()) return nullptr;
    return vec.back();
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