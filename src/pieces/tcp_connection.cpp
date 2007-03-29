
#include "Pieces/TCPConnection"
#include "Pieces/TCPSocket"
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
};


TCPConnectionPrivate::TCPConnectionPrivate()
: socket(0)
, receiver(0)
{
}


TCPConnection::TCPConnection(TCPSocket* socket)
: d(new TCPConnectionPrivate)
{
    d->socket = socket;
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


void TCPConnection::sendMessage(int messageType, const ByteArray& data)
{
    DataStream ds(d->socket.get());

    // TODO: Maybe use a MessageHeader class?
    ds << messageType << data << flush;
}

} // namespace Pieces
