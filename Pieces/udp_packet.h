
#ifndef PIECES_UDP_PACKET_H
#define PIECES_UDP_PACKET_H

#include "Pieces/SharedData"
#include "Pieces/SharedDataPointer"
#include "Pieces/ByteArray"
#include "Pieces/SocketAddress"


namespace Pieces
{

class UDPPacket
{
public:
    UDPPacket();
    UDPPacket(const ByteArray& data, const SocketAddress& addr);
    UDPPacket(const ByteArray& data, const InetAddress& addr, port_t port);

    // Copy operations (this class might use implicit sharing)
    UDPPacket(const UDPPacket& other);
    UDPPacket& operator=(const UDPPacket& other);

    ~UDPPacket();

    SocketAddress getAddress() const;
    void setAddress(const SocketAddress& addr);

    ByteArray getData() const;
    void setData(const ByteArray& data);

private:
    class Data : public SharedData
    {
    public:
        Data();
        Data(const ByteArray& data, const SocketAddress& addr);

        Data(const Data& other);
        Data& operator=(const Data& other);

        ByteArray data;
        SocketAddress address;
    };

    SharedDataPointer<Data> d;
};

} // namespace Pieces

#endif // PIECES_UDP_PACKET_H
