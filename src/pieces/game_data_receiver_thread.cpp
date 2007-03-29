
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
    GameData* buffer;
};


GameDataReceiverThreadPrivate::GameDataReceiverThreadPrivate()
: socket(0)
, eventLoop(0)
, buffer(0)
{
}


GameDataReceiverThread::GameDataReceiverThread(EventLoop* eventLoop, GameData* buffer, port_t port)
: d(new GameDataReceiverThreadPrivate)
{
    d->socket = new UDPSocket;
    d->socket->bind(port);

    d->buffer = buffer;
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
            FrameData frame;
            bs >> frameNum >> frame;

            // TODO: Maybe the event should contain the data, instead of adding to the buffer here.
            // With implicit sharing, we can pass this around, and don't need to share data across threads.
            // With an internal event loop, we could buffer the data internally at the "main" thread.
            d->buffer->setFrameData(frameNum, frame);

            // Notify
            d->eventLoop->postEvent(new GameDataEvent(frameNum, frame));
        }
    }
    catch (const Exception& e)
    {
        PERROR << e;
    }
}

} // namespace Pieces
