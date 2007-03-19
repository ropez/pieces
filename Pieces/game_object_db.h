
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
 * \brief Collection of game objects.
 *
 * This class holds a collection of pointers to game objects, indexed by object
 * id. Each object is represented by a reference pointer, stored in a map.
 *
 * \see GameObject
 * \author Robin Pedersen
 */
class GameObjectDB
{
public:

    /**
     * Pointer type to a game object.
     */
    typedef ReferencePointer<GameObject> ptr_t;

    /**
     * Map type used by this class.
     */
    typedef std::map<objectid_t, ptr_t> map_t;


    /**
     * Default constructor creates an empty collection.
     */
    GameObjectDB();

    /**
     * Destructor.
     *
     * \note Since the objects are stored with reference pointers, deleting
     * this collection may cause objects to be deleted if they are not
     * referenced elsewhere.
     */
    ~GameObjectDB();

    /**
     * Removes all entries.
     *
     * \note Since the objects are stored with reference pointers, clearing
     * this collection may cause objects to be deleted if they are not
     * referenced elsewhere.
     */
    void clear();

    /**
     * Insert object \a obj into the collection.
     *
     * Returns a pointer to the object replaced, or 0 if no object was replaced.
     */
    ptr_t insert(objectid_t objectId, GameObject* obj);

    /**
     * Remove the object with the given \a objectId from the collection.
     */
    ptr_t remove(objectid_t objectId);

    /**
     * Remove the entry at the iterator position.
     *
     * Returns a pointer to the removed object. If the returned value is ignored,
     * and the object isn't referenced from elsewhere, it will be deleted by the
     * reference pointer.
     */
    ptr_t remove(map_t::iterator it);

    /**
     * Encode object data for all objects.
     *
     * Update the frame date referenced by \a frame by calling the
     * \link GameObject::encode() encode() \endlink function in all object,
     * and storing the results in \a frame.
     */
    void update(FrameData& frame) const;

    /**
     * Decode object data for all objects.
     *
     * Update all objects by reading from the frame data referenced by \a frame,
     * and calling the decode function in all objects.
     */
    void apply(const FrameData& frame);

    /**
     * Returns an iterator at the beginning of the map.
     *
     * This allows low-level operations directly on the internal map.
     */
    map_t::iterator begin();

    /**
     * Returns an iterator at the end of the map.
     *
     * This allows low-level operations directly on the internal map.
     */
    map_t::iterator end();

    /**
     * Returns an immutable iterator at the beginning of the map.
     *
     * This allows low-level operations directly on the internal map.
     */
    map_t::const_iterator begin() const;

    /**
     * Returns an immutable iterator at the end of the map.
     *
     * This allows low-level operations directly on the internal map.
     */
    map_t::const_iterator end() const;

private:
    // Disable copy operations
    GameObjectDB(const GameObjectDB&);
    GameObjectDB& operator=(const GameObjectDB&);

    map_t m_objects;
};

} // namespace Pieces

#endif // PIECES_GAME_OBJECT_DB
