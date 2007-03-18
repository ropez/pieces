
#ifndef PIECES_GAME_OBJECT_H
#define PIECES_GAME_OBJECT_H

#include "Pieces/Object"
#include "Pieces/HostObjectIface"
#include "Pieces/PeerObjectIface"


namespace Pieces
{


/**
 * \class GameObject
 * \brief Abstract base class for objects defined for both host and peer.
 *
 * This is a base class provided for convenience.
 *
 * This should be used as base class for objects, if the game programmer wants
 * to use the same object classes in the host and the peers.
 *
 * Subclasses must implement both the HostObjectIface and the PeerObjectIface.
 *
 * \see HostGameObject, PeerGameObject
 * \author Robin Pedersen
 */
class GameObject : public Object, public HostObjectIface, public PeerObjectIface
{
public:
    GameObject(objectid_t objectId);
    virtual ~GameObject();

private:
    // Disable copy operations
    GameObject(const GameObject&);
    GameObject& operator=(const GameObject&);
};

} // namespace Pieces

#endif // PIECES_GAME_OBJECT_H
