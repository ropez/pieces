
#include "Pieces/GameObjectDB"
#include "Pieces/GameObject"


namespace Pieces
{


GameObjectDB::GameObjectDB()
: m_objects()
{
}


GameObjectDB::~GameObjectDB()
{
}


void GameObjectDB::clear()
{
    m_objects.clear();
}


GameObjectDB::ptr_t GameObjectDB::insert(objectid_t objectId, GameObject* obj)
{
    ptr_t tmp = remove(objectId);
    m_objects[objectId] = obj;
    return tmp;
}


GameObjectDB::ptr_t GameObjectDB::remove(objectid_t objectId)
{
    map_t::iterator it = m_objects.find(objectId);

    return remove(it);
}


GameObjectDB::ptr_t GameObjectDB::remove(map_t::iterator it)
{
    if (it != end())
    {
        ptr_t tmp = it->second;
        m_objects.erase(it);
        return tmp;
    }
    return 0;
}


void GameObjectDB::update(FrameData& frame) const
{
    for (map_t::const_iterator it = begin(); it != end(); ++it)
    {
        const ptr_t obj = it->second;
        obj->update(frame);
    }
}


void GameObjectDB::apply(const FrameData& frame)
{
    for (map_t::iterator it = begin(); it != end(); ++it)
    {
        ptr_t obj = it->second;
        obj->apply(frame);
    }
}


GameObjectDB::map_t::iterator GameObjectDB::begin()
{
    return m_objects.begin();
}


GameObjectDB::map_t::iterator GameObjectDB::end()
{
    return m_objects.end();
}


GameObjectDB::map_t::const_iterator GameObjectDB::begin() const
{
    return m_objects.begin();
}


GameObjectDB::map_t::const_iterator GameObjectDB::end() const
{
    return m_objects.end();
}

} // namespace Pieces
