
#include "Pieces/TCPConnection"
#include "Pieces/TCPSocket"
#include "Pieces/Message"
#include "Pieces/MessageQueue"
#include "Pieces/TCPReceiverThread"
#include "Pieces/DataStream"
#include "Pieces/AutoPointer"


namespace Pieces
{

class TCPConnectionPrivate
{
public:
    TCPConnectionPrivate();

    AutoPointer<TCPSocket> socket;
    AutoPointer<TCPReceiverThread> receiver;

    AutoPointer<MessageQueue> queue;
};


TCPConnectionPrivate::TCPConnectionPrivate()
: socket(0)
, receiver(0)
, queue(0)
{
}


TCPConnection::TCPConnection(TCPSocket* socket)
: d(new TCPConnectionPrivate)
{
    d->socket = socket;
    d->queue = new MessageQueue;
}


TCPConnection::~TCPConnection()
{
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


void TCPConnection::sendMessage(const Message& message)
{
    d->queue->push(message);

    DataStream ds(d->socket.get());

    // TODO: Use a different thread to pop and send
    ds << d->queue->pop() << flush;
}

} // namespace Pieces
