
#include "Pieces/GameDataReceiverThread"
#include "Pieces/EventLoop"
#include "Pieces/FrameData"
#include "Pieces/GameData"
#include "Pieces/UDPSocket"
#include "Pieces/Datagram"
#include "Pieces/BufferStream"
#include "Pieces/GameDataEvent"
#include "Pieces/Exception"
#include "Pieces/AutoPointer"
#include "Pieces/Debug"

#include "OpenThreads/Mutex"
#include "OpenThreads/ScopedLock"


namespace Pieces
{
using namespace OpenThreads;

class GameDataReceiverThreadPrivate
{
public:
    GameDataReceiverThreadPrivate();

    Mutex mutex;

    AutoPointer<UDPSocket> socket;

    EventLoop* eventLoop;
};


GameDataReceiverThreadPrivate::GameDataReceiverThreadPrivate()
: socket(0)
, eventLoop(0)
{
}


GameDataReceiverThread::GameDataReceiverThread(EventLoop* eventLoop, port_t port)
: d(new GameDataReceiverThreadPrivate)
{
    d->socket = new UDPSocket;
    d->socket->bind(port);

    d->eventLoop = eventLoop;
}


GameDataReceiverThread::~GameDataReceiverThread()
{
    abort();
    delete d;
}


void GameDataReceiverThread::abort()
{
    ScopedLock<Mutex> lock(d->mutex);

    if (isRunning())
    {
        cancel();

        // Allow thread to exit
        ReverseScopedLock<Mutex> unlock(d->mutex);
        join();
    }
}


void GameDataReceiverThread::run()
{
    const size_t MAX_PACKET_SIZE = 0x1000;

    ScopedLock<Mutex> lock(d->mutex);

    try
    {
        for (;;)
        {
            Datagram dg;
            {
                ReverseScopedLock<Mutex> unlock(d->mutex);

                dg = d->socket->receive(MAX_PACKET_SIZE);
            }

            BufferStream bs(dg.getData());

            framenum_t frameNum = 0;
            FrameData frameData;
            bs >> frameNum >> frameData;

            // Notify
            d->eventLoop->postEvent(new GameDataEvent(frameNum, frameData));
        }
    }
    catch (const Exception& e)
    {
        PERROR << e;
    }
}

} // namespace Pieces
