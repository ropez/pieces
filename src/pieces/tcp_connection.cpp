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

#include "Pieces/TCPConnection"
#include "Pieces/TCPSocket"
#include "Pieces/Message"
#include "Pieces/MessageQueue"
#include "Pieces/TCPReceiverThread"
#include "Pieces/TCPSenderThread"
#include "Pieces/DataStream"
#include "Pieces/AutoPointer"


namespace pcs
{

class TCPConnectionPrivate
{
public:
    TCPConnectionPrivate();

    AutoPointer<TCPSocket> socket;

    AutoPointer<MessageQueue> queue;

    AutoPointer<TCPReceiverThread> receiver;
    AutoPointer<TCPSenderThread> sender;
};


TCPConnectionPrivate::TCPConnectionPrivate()
: socket(0)
, queue(0)
, receiver(0)
, sender(0)
{
}


TCPConnection::TCPConnection(TCPSocket* socket)
: d(new TCPConnectionPrivate)
{
    d->socket = socket;
}


TCPConnection::~TCPConnection()
{
    stopSending();
    stopReceiving();

    delete d;
}


SocketAddress TCPConnection::getPeerAddress() const
{
    return d->socket->getPeerAddress();
}


void TCPConnection::startReceiving(EventLoop* eventLoop)
{
    d->receiver = new TCPReceiverThread(d->socket.get(), eventLoop);
    d->receiver->start();
}


void TCPConnection::stopReceiving()
{
    // Stop and delete receiver thread by replacing auto-pointer
    d->receiver = 0;
}


void TCPConnection::startSending(const std::deque<msgpair_t>& messages)
{
    d->queue = new MessageQueue(messages);

    d->sender = new TCPSenderThread(d->socket.get(), d->queue.get());
    d->sender->start();
}


void TCPConnection::stopSending()
{
    // Stop and delete sender thread by replacing auto-pointer
    d->sender = 0;

    // Delete pending messages
    d->queue = 0;
}


void TCPConnection::sendMessage(const msgpair_t& message)
{
    if (d->queue.isValid())
    {
        d->queue->push(message);
    }
}

} // namespace pcs
