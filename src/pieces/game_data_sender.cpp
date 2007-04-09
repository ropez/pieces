
#include "Pieces/GameDataSender"
#include "Pieces/FrameData"
#include "Pieces/GameData"
#include "Pieces/AutoPointer"
#include "Pieces/UDPSocket"
#include "Pieces/Datagram"
#include "Pieces/BufferStream"

#include <set>


namespace Pieces
{

class GameDataSenderPrivate
{
public:
    GameDataSenderPrivate();

    AutoPointer<UDPSocket> socket;
    std::set<SocketAddress> receivers;

    framenum_t frameNumber;
    GameData buffer;
};


GameDataSenderPrivate::GameDataSenderPrivate()
: socket(0)
, frameNumber(0)
, buffer()
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


FrameData GameDataSender::getFrameData(framenum_t frameNum) const
{
    return d->buffer.getFrameData(frameNum);
}


void GameDataSender::sendFrameData(const FrameData& frame)
{
    d->buffer.setFrameData(d->frameNumber, frame);

    BufferStream bs;
    bs << d->frameNumber << frame;

    for (std::set<SocketAddress>::const_iterator it = d->receivers.begin(); it != d->receivers.end(); ++it)
    {
        Datagram dg(bs.data(), *it);
        d->socket->send(dg);
    }

    ++d->frameNumber;
}

} //namespace Pieces
