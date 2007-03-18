
#ifndef PIECES_PEER_GAME_OBJECT_H
#define PIECES_PEER_GAME_OBJECT_H

#include "Pieces/Object"
#include "Pieces/PeerObjectIface"

namespace Pieces
{


/**
 * \class PeerGameObject
 * \brief Abstract base class for objects defined for peers only.
 *
 * This is a base class provided for convenience.
 *
 * This should be used as base class for objects, if the game programmer wants
 * to use specialized object classes only in the peers.
 *
 * Subclasses must implement the PeerObjectIface.
 *
 * \see GameObject, HostGameObject
 * \author Robin Pedersen
 */
class PeerGameObject : public Object, public PeerObjectIface
{
public:
    PeerGameObject(objectid_t objectId);
    virtual ~PeerGameObject();

private:
    // Disable copy operations
    PeerGameObject(const PeerGameObject&);
    PeerGameObject& operator=(const PeerGameObject&);
};

} // namespace Pieces

#endif // PIECES_PEER_GAME_OBJECT_H
