/*
    Copyright 2007,2010 The Pieces Team

    This file is part of Pieces.

    Pieces is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Pieces is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
    more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Pieces.  If not, see <http://www.gnu.org/licenses/>.
*/

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
