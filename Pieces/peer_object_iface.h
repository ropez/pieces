
#ifndef PIECES_PEER_OBJECT_IFACE_H
#define PIECES_PEER_OBJECT_IFACE_H


namespace Pieces
{
class DataStream;


/**
 * \class PeerObjectIface
 * \brief Peer object interface.
 *
 * In addition to being an Object. Objects defined for the peer processes must
 * implement this interface.
 *
 * \author Robin Pedersen
 */
class PeerObjectIface
{
public:
    virtual ~PeerObjectIface() {};

    virtual void decode(DataStream& ds) = 0;

};

} // namespace Pieces

#endif // PIECES_PEER_OBJECT_IFACE_H
