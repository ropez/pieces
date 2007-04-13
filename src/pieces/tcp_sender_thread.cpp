
#include "Pieces/TCPSenderThread"
#include "Pieces/TCPSocket"
#include "Pieces/DataStream"
#include "Pieces/Message"
#include "Pieces/MessageQueue"
#include "Pieces/Exception"
#include "Pieces/Debug"

#include "OpenThreads/Mutex"
#include "OpenThreads/ScopedLock"


namespace Pieces
{
using namespace OpenThreads;

class TCPSenderThreadPrivate
{
public:
    TCPSenderThreadPrivate();

    Mutex mutex;

    TCPSocket* socket;
    MessageQueue* queue;
};


TCPSenderThreadPrivate::TCPSenderThreadPrivate()
: socket(0)
, queue(0)
{
}


TCPSenderThread::TCPSenderThread(TCPSocket* socket, MessageQueue* queue)
: Thread()
, d(new TCPSenderThreadPrivate)
{
    d->socket = socket;
    d->queue = queue;
}


TCPSenderThread::~TCPSenderThread()
{
    abort();
    delete d;
}


void TCPSenderThread::abort()
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


void TCPSenderThread::run()
{
    ScopedLock<Mutex> lock(d->mutex);

    try
    {
        DataStream ds(d->socket);

        for (;;)
        {
            // Pop message from queue
            msgpair_t msg;
            {
                // Release lock while blocked (most of the time)
                ReverseScopedLock<Mutex> unlock(d->mutex);

                msg = d->queue->pop();
            }

            // Send message
            ds << msg.first << msg.second << flush;
        }
    }
    catch (const Exception& e)
    {
        PERROR << e;
    }
}

} // namespace Pieces
