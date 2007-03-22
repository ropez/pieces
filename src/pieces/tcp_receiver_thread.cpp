#include "Pieces/TCPReceiverThread"
#include "Pieces/Debug"
#include "Pieces/NetworkEvent"
#include "Pieces/DataStream"
#include "Pieces/TCPSocket"
#include "Pieces/EventLoop"
#include "Pieces/Exception"
#include "Pieces/TimeoutException"
#include "Pieces/DisconnectedException"

#include "OpenThreads/Mutex"
#include "OpenThreads/ScopedLock"

using namespace OpenThreads;


namespace Pieces
{

class TCPReceiverThreadPrivate
{
public:
    TCPReceiverThreadPrivate();

    Mutex mutex;

    TCPSocket* socket;
    EventLoop* eventLoop;
};


TCPReceiverThreadPrivate::TCPReceiverThreadPrivate()
: mutex()
, socket(0)
, eventLoop(0)
{
}


TCPReceiverThread::TCPReceiverThread(TCPSocket* socket, EventLoop* eventLoop)
: OpenThreads::Thread()
, d(new TCPReceiverThreadPrivate)
{
    d->socket = socket;
    d->eventLoop = eventLoop;
}


TCPReceiverThread::~TCPReceiverThread()
{
    abort();
    delete d;
}


void TCPReceiverThread::abort()
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


void TCPReceiverThread::run()
{
    ScopedLock<Mutex> lock(d->mutex);

    try
    {
        PDEBUG << "Receiver thread started";

        DataStream ds(d->socket);

        for (;;)
        {
            try
            {
                int messageType = NetworkEvent::NO_MESSAGE_TYPE;
                ByteArray data;

                {
                    // Release lock while blocked (most of the time)
                    ReverseScopedLock<Mutex> unlock(d->mutex);

                    ds >> messageType;
                    ds >> data;
                }

                AutoPointer<NetworkEvent> e(new NetworkEvent(NetworkEvent::RECEIVED_MESSAGE, d->socket->getPeerAddress()));
                e->setMessageType(messageType);
                e->setData(data);
                d->eventLoop->postEvent(e.release());
            }
            catch (const TimeoutException&)
            {
                // Ignore, try again
            }
        }
    }
    catch (const DisconnectedException&)
    {
        d->eventLoop->postEvent(new NetworkEvent(NetworkEvent::DISCONNECTED, d->socket->getPeerAddress()));
    }
    catch (const Exception& e)
    {
        PERROR << e;
    }
}

} // namespace Pieces
