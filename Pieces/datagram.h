
#ifndef PIECES_DATAGRAM_H
#define PIECES_DATAGRAM_H

#include "Pieces/SharedData"
#include "Pieces/SharedDataPointer"
#include "Pieces/ByteArray"
#include "Pieces/SocketAddress"


namespace Pieces
{

class Datagram
{
public:
    Datagram();
    Datagram(const ByteArray& data, const SocketAddress& addr);
    Datagram(const ByteArray& data, const InetAddress& addr, port_t port);

    // Copy operations
    Datagram(const Datagram& other);
    Datagram& operator=(const Datagram& other);

    ~Datagram();

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

#endif // PIECES_DATAGRAM_H
