
#ifndef PIECES_HOST_OBJECT_IFACE_H
#define PIECES_HOST_OBJECT_IFACE_H


namespace Pieces
{
class DataStream;


/**
 * \class HostObjectIface
 * \brief Host object interface.
 *
 * In addition to being an Object. Objects defined for the host process must
 * implement this interface.
 *
 * \author Robin Pedersen
 */
class HostObjectIface
{
public:
    virtual ~HostObjectIface() {};

    virtual void encode(DataStream& ds) const = 0;

};

} // namespace Pieces

#endif // PIECES_HOST_OBJECT_IFACE_H
