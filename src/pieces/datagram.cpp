
#include "Pieces/Datagram"
#include "Pieces/ByteArray"
#include "Pieces/InetAddress"


namespace pcs
{

Datagram::Datagram()
: d(new Data)
{
}


Datagram::Datagram(const ByteArray& data, const SocketAddress& addr)
: d(new Data(data, addr))
{
}


Datagram::Datagram(const ByteArray& data, const InetAddress& addr, port_t port)
: d(new Data(data, SocketAddress(addr, port)))
{
}


Datagram::~Datagram()
{
}


Datagram::Datagram(const Datagram& other)
{
    d = other.d;
}


Datagram& Datagram::operator=(const Datagram& other)
{
    d = other.d;

    return *this;
}


SocketAddress Datagram::getAddress() const
{
    return d->address;
}


void Datagram::setAddress(const SocketAddress& addr)
{
    d->address = addr;
}


ByteArray Datagram::getData() const
{
    return d->data;
}


void Datagram::setData(const ByteArray& data)
{
    d->data = data;
}


Datagram::Data::Data()
: SharedData()
, data()
, address()
{
}


Datagram::Data::Data(const ByteArray& data, const SocketAddress& addr)
: SharedData()
, data(data)
, address(addr)
{
}


Datagram::Data::Data(const Data& other)
: SharedData()
, data(other.data)
, address(other.address)
{
}


Datagram::Data& Datagram::Data::operator=(const Data& other)
{
    data = other.data;
    address = other.address;

    return *this;
}

} // namespace pcs
