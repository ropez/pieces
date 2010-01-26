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

#include "Pieces/GameDataSender"
#include "Pieces/FrameData"
#include "Pieces/GameData"
#include "Pieces/AutoPointer"
#include "Pieces/UDPSocket"
#include "Pieces/Datagram"
#include "Pieces/BufferStream"

#include <set>


namespace pcs
{

class GameDataSenderPrivate
{
public:
    GameDataSenderPrivate();

    AutoPointer<UDPSocket> socket;
    std::set<SocketAddress> receivers;

    framenum_t frameNumber;
};


GameDataSenderPrivate::GameDataSenderPrivate()
: socket(0)
, frameNumber(0)
{
}


GameDataSender::GameDataSender()
: d(new GameDataSenderPrivate)
{
    d->socket = new UDPSocket;
}


GameDataSender::~GameDataSender()
{
    delete d;
}


framenum_t GameDataSender::getFrameNumber() const
{
    return d->frameNumber;
}


void GameDataSender::addReceiver(const SocketAddress& address)
{
    d->receivers.insert(address);
}


void GameDataSender::removeReceiver(const SocketAddress& address)
{
    d->receivers.erase(address);
}


void GameDataSender::sendFrameData(const FrameData& frameData)
{
    // TODO: Background thread!

    BufferStream bs;
    bs << d->frameNumber << frameData;

    for (std::set<SocketAddress>::const_iterator it = d->receivers.begin(); it != d->receivers.end(); ++it)
    {
        Datagram dg(bs.data(), *it);
        d->socket->send(dg);
    }

    ++d->frameNumber;
}

} //namespace pcs
