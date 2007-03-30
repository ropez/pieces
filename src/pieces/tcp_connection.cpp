
#include "Pieces/TCPConnection"
#include "Pieces/TCPSocket"
#include "Pieces/Message"
#include "Pieces/MessageQueue"
#include "Pieces/TCPReceiverThread"
#include "Pieces/TCPSenderThread"
#include "Pieces/DataStream"
#include "Pieces/AutoPointer"


namespace Pieces
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


void TCPConnection::startSending(const std::deque<Message>& messages)
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


void TCPConnection::sendMessage(const Message& message)
{
    if (d->queue.isValid())
    {
        d->queue->push(message);
    }
}

} // namespace Pieces
