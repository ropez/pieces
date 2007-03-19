
#ifndef PIECES_GAME_OBJECT_DB
#define PIECES_GAME_OBJECT_DB

#include "Pieces/global"
#include "Pieces/ReferencePointer"

#include <map>

namespace Pieces
{
class GameObject;
class FrameData;


/**
 * \class GameObjectDB
 *
 *
 * \author Robin Pedersen
 */
class GameObjectDB
{
public:
    typedef ReferencePointer<GameObject> ptr_t;
    typedef std::map<objectid_t, ptr_t> map_t;

    GameObjectDB();
    ~GameObjectDB();

    void clear();

    /**
     * Returns a pointer to the object replaced, or 0 if no object was replaced.
     */
    ptr_t insert(objectid_t objectId, GameObject* obj);

    ptr_t remove(objectid_t objectId);
    ptr_t remove(map_t::iterator it);

    void update(FrameData& frame) const;
    void apply(const FrameData& frame);

    map_t::iterator begin();
    map_t::iterator end();

    map_t::const_iterator begin() const;
    map_t::const_iterator end() const;

private:
    // Disable copy operations
    GameObjectDB(const GameObjectDB&);
    GameObjectDB& operator=(const GameObjectDB&);

    map_t m_objects;
};

} // namespace Pieces

#endif // PIECES_GAME_OBJECT_DB
