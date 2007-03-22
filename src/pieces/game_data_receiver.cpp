
#include "Pieces/GameDataReceiver"
#include "Pieces/GameDataReceiverThread"
#include "Pieces/GameData"
#include "Pieces/IOException"
#include "Pieces/AutoPointer"
#include "Pieces/Debug"



namespace Pieces
{

class GameDataReceiverPrivate
{
public:
    GameDataReceiverPrivate();

    AutoPointer<GameDataReceiverThread> thread;

    EventLoop* eventLoop;
    GameData buffer;
};

GameDataReceiverPrivate::GameDataReceiverPrivate()
: thread(0)
, eventLoop(0)
, buffer()
{
}


GameDataReceiver::GameDataReceiver(EventLoop* eventLoop)
: d(new GameDataReceiverPrivate)
{
    d->eventLoop = eventLoop;
}


GameDataReceiver::~GameDataReceiver()
{
    delete d;
}


void GameDataReceiver::listen(port_t port)
{
    try
    {
        d->thread = new GameDataReceiverThread(d->eventLoop, &d->buffer, port);
        d->thread->start();
    }
    catch (const IOException& e)
    {
        PERROR << e.getMessage();
    }
}


FrameData GameDataReceiver::getFrameData(framenum_t frameNum)
{
    return d->buffer.getFrameData(frameNum);
}


} //namespace Pieces
