
#ifndef PIECES_UDP_PACKET_H
#define PIECES_UDP_PACKET_H

#include "Pieces/ByteArray"
#include "Pieces/InetAddress"
#include "Pieces/UDPPacket"

namespace Pieces
{

class UDPPacket
{
public:
    UDPPacket();
    UDPPacket(const ByteArray& data);
    UDPPacket(const ByteArray& data, const InetAddress& addr, short port);
    // etc...

    // Copy operations (this class might use implicit sharing)
    UDPPacket(const UDPPacket& other);
    UDPPacket& operator=(const UDPPacket& other);

    ~UDPPacket();

    short getPort() const;
    void setPort(short port);

    InetAddress getAddress() const;
    void setAddress(const InetAddress& adr);

    ByteArray getData() const;
    void setData(const ByteArray& data);

};

} // namespace Pieces

#endif // PIECES_UDP_PACKET_H
