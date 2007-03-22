
#include "Pieces/GameObjectDB"
#include "Pieces/GameObject"
#include "Pieces/FrameData"
#include "Pieces/BufferStream"
#include "Pieces/IOException"
#include "Pieces/Debug"


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
        objectid_t id = it->first;
        const ptr_t obj = it->second;

        // Object data
        BufferStream s;
        obj->encode(s);

        frame.setObjectData(id, s.data());
    }
}


void GameObjectDB::apply(const FrameData& frame)
{
    for (map_t::iterator it = begin(); it != end(); ++it)
    {
        objectid_t id = it->first;
        ptr_t obj = it->second;

        // Object data
        BufferStream s(frame.getObjectData(id));


        // TODO: Don't catch exception here
        try
        {
            // Decode object data into stream
            obj->decode(s);
        }
        catch (const IOException& e)
        {
            PERROR << e;
        }
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
