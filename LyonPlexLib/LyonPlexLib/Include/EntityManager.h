#pragma once
//#include <cstddef>

//-----------------------------------------------------------------------------//
// Entity definition
//-----------------------------------------------------------------------------//
struct Entity
{
    uint32_t id;
};

//-----------------------------------------------------------------------------//
// SparseSet-based EntityManager
//-----------------------------------------------------------------------------//
class EntityManager 
{
public:
    EntityManager(size_t maxEntities = 4096);//nombre max d'entité par scene

    Entity Create();

    void Destroy(Entity e);

    void ClearAllEntities();

    bool Exists(Entity e) const;

    const std::vector<uint32_t>& GetAll() const { return m_dense; }

    size_t GetEntityCount() { return m_dense.size(); }

private:
    uint32_t m_nextId = 0;
    std::vector<uint32_t> m_dense;
    std::vector<uint32_t> m_sparse;
    std::vector<uint32_t> m_freeList;
};