
#include "Pieces/TCPListenerThread"
#include "Pieces/TCPReceiverThread"
#include "Pieces/TCPServer"
#include "Pieces/TCPSocket"
#include "Pieces/EventLoop"
#include "Pieces/DataStream"
#include "Pieces/Exception"
#include "Pieces/Debug"

#include "OpenThreads/Mutex"
#include "OpenThreads/ScopedLock"
#include "OpenThreads/Thread"


namespace Pieces
{

using namespace OpenThreads;

class TCPListenerThreadPrivate
{
public:
    TCPListenerThreadPrivate();

    Mutex mutex;

    port_t port;
    EventLoop* eventLoop;
};


TCPListenerThreadPrivate::TCPListenerThreadPrivate()
: mutex()
, port(0)
, eventLoop(0)
{
}


TCPListenerThread::TCPListenerThread(port_t port, EventLoop* eventLoop)
: d(new TCPListenerThreadPrivate)
{
    d->port = port;
    d->eventLoop = eventLoop;
}


TCPListenerThread::~TCPListenerThread()
{
    abort();
    delete d;
}


void TCPListenerThread::abort()
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


void TCPListenerThread::run()
{
    ScopedLock<Mutex> lock(d->mutex);

    try
    {
        TCPServer server;
        server.listen(d->port);

        DEBUG << "Server listening";

        for (;;)
        {
            AutoPointer<TCPSocket> s;

            {
                // Release lock while blocked (most of the time)
                ReverseScopedLock<Mutex> unlock(d->mutex);

                s = server.accept();
            }

            INFO << "Accepted connection from " << s->getPeerAddress();

            // TODO: This is a memory leak!
            TCPReceiverThread* session = new TCPReceiverThread(s.release(), d->eventLoop);
            session->start();
        }
    }
    catch (const Exception& e)
    {
        ERROR << e;
    }
}


} // namespace Pieces
