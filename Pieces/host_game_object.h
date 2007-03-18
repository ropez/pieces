
#ifndef PIECES_HOST_GAME_OBJECT_H
#define PIECES_HOST_GAME_OBJECT_H

#include "Pieces/Object"
#include "Pieces/HostObjectIface"

namespace Pieces
{


/**
 * \class HostGameObject
 * \brief Abstract base class for objects defined for host only.
 *
 * This is a base class provided for convenience.
 *
 * This should be used as base class for objects, if the game programmer wants
 * to use specialized object classes only in the host.
 *
 * Subclasses must implement the HostObjectIface.
 *
 * \see GameObject, PeerGameObject
 * \author Robin Pedersen
 */
class HostGameObject : public Object, public HostObjectIface
{
public:
    HostGameObject(objectid_t objectId);
    virtual ~HostGameObject();

private:
    // Disable copy operations
    HostGameObject(const HostGameObject&);
    HostGameObject& operator=(const HostGameObject&);
};

} // namespace Pieces

#endif // PIECES_HOST_GAME_OBJECT_H
