
#include "Pieces/GameDataReceiver"
#include "Pieces/GameDataReceiverThread"
#include "Pieces/GameData"
#include "Pieces/IOException"
#include "Pieces/AutoPointer"
#include "Pieces/Debug"



namespace pcs
{

class GameDataReceiverPrivate
{
public:
    GameDataReceiverPrivate();

    AutoPointer<GameDataReceiverThread> thread;

    EventLoop* eventLoop;
};

GameDataReceiverPrivate::GameDataReceiverPrivate()
: thread(0)
, eventLoop(0)
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
    d->thread = new GameDataReceiverThread(d->eventLoop, port);
    d->thread->start();
}

} //namespace pcs
