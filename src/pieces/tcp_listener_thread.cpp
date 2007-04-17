
#include "Pieces/TCPListenerThread"
#include "Pieces/TCPConnection"
#include "Pieces/TCPConnectionManager"
#include "Pieces/TCPServer"
#include "Pieces/TCPSocket"
#include "Pieces/Exception"
#include "Pieces/Debug"

#include "OpenThreads/Mutex"
#include "OpenThreads/ScopedLock"
#include "OpenThreads/Thread"


namespace pcs
{

using namespace OpenThreads;

class TCPListenerThreadPrivate
{
public:
    TCPListenerThreadPrivate();

    Mutex mutex;

    AutoPointer<TCPServer> server;

    port_t port;
    TCPConnectionManager* manager;
};


TCPListenerThreadPrivate::TCPListenerThreadPrivate()
: mutex()
, server(0)
, port(0)
, manager(0)
{
}


TCPListenerThread::TCPListenerThread(port_t port, TCPConnectionManager* manager)
: d(new TCPListenerThreadPrivate)
{
    d->port = port;
    d->manager = manager;

    d->server = new TCPServer;
    d->server->listen(d->port);
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
        PDEBUG << "Server listening";

        for (;;)
        {
            AutoPointer<TCPSocket> s;

            {
                // Release lock while blocked (most of the time)
                ReverseScopedLock<Mutex> unlock(d->mutex);

                s = d->server->accept();
            }

            PINFO << "Accepted connection from " << s->getPeerAddress();

            // Add connection to manager
            d->manager->add(new TCPConnection(s.release()));
        }
    }
    catch (const Exception& e)
    {
        PERROR << e;
    }
}


} // namespace pcs
