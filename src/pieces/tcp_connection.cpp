
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


void TCPConnection::startReceiver(EventLoop* eventLoop)
{
    d->receiver = new TCPReceiverThread(d->socket.get(), eventLoop);
    d->receiver->start();
}


void TCPConnection::sendMessage(int messageType, const ByteArray& data)
{
    DataStream ds(d->socket.get());
    ds << messageType << data << flush;
}

} // namespace Pieces
