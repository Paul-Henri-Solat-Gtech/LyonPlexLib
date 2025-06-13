#pragma once
#include <string>

template<typename T, typename Key = std::string>
class ResourceManager 
{
public:
    using ResourceID = uint32_t;

    ResourceManager() = default;
    ~ResourceManager() { Clear(); }

    // Charge une ressource Åa partir d'une clÅe (ex: chemin fichier).
    // Si dejÅa chargee, renvoie l'ID existant.
    ResourceID Load(const Key& key) 
    {
        auto it = m_lookup.find(key);
        if (it != m_lookup.end()) 
        {
            return it->second;
        }
        // Sinon, charge et ajoute
        ResourceID newID = static_cast<ResourceID>(m_resources.size());
        m_resources.emplace_back();
        m_keys.push_back(key);
        m_lookup[key] = newID;
        // Ici, on appelle la methode T::LoadFromFile 
        m_resources[newID].LoadFromFile(key);
        return newID;
    }

    // Ajoute manuellement une ressource dejÅa remplie et renvoie son ID
    ResourceID Add(const T& data) 
    {
        ResourceID newID = static_cast<ResourceID>(m_resources.size());
        m_resources.push_back(data);
        m_keys.push_back(""); // clÅe vide ou personnalisable
        return newID;
    }

    void AddManual(const Key& key)
    {
        auto it = m_lookup.find(key);
        if (it != m_lookup.end())
        {
            return it->second;
        }
        // Sinon, charge et ajoute
        ResourceID newID = static_cast<ResourceID>(m_resources.size());
        m_resources.emplace_back();
        m_keys.push_back(key);
        m_lookup[key] = newID;
        // Ici, on appelle la methode T::LoadFromFile 
        m_resources[newID].CreateTriangle();
        return newID;
    }

    // Acces Åa la ressource par ID
    const T& Get(ResourceID id) const 
    {
        assert(id < m_resources.size() && "Invalid resource ID");
        return m_resources[id];
    }
    T& Get(ResourceID id) 
    {
        assert(id < m_resources.size() && "Invalid resource ID");
        return m_resources[id];
    }

    // Verifie si une clÅe est dejÅa chargee
    bool Has(const Key& key) const 
    {
        return m_lookup.find(key) != m_lookup.end();
    }

    void Remove(ResourceID id)
    {
        if (id >= m_resources.size()) return;

        // Invalider la ressource
        m_resources[id] = T{};
        m_keys[id] = Key{};

        // Supprimer l'entrÈe du cache
        for (auto it = m_lookup.begin(); it != m_lookup.end(); ++it) {
            if (it->second == id) {
                m_lookup.erase(it);
                break;
            }
        }
    }

    // Liberation de toutes les ressources
    void Clear() 
    {
        for (auto& res : m_resources) 
        {
            res.Unload();
        }
        m_resources.clear();
        m_keys.clear();
        m_lookup.clear();
    }

    // Nombre de ressources chargees
    size_t Count() const { return m_resources.size(); }

private:
    std::vector<T> m_resources;
    std::vector<Key> m_keys;
    std::unordered_map<Key, ResourceID> m_lookup;
};


