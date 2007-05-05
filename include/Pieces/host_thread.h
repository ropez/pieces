
#ifndef PIECES_HOST_THREAD_H
#define PIECES_HOST_THREAD_H

#include "Pieces/global"
#include "OpenThreads/Thread"


namespace pcs
{
class Host;


/**
 * \class HostThread host_thread.h <Pieces/HostThread>
 * \brief Thread that executes a host.
 *
 * This is a convenience class that can be used to run a host in a background
 * thread.
 *
 * \author Robin Pedersen
 */
class HostThread : public OpenThreads::Thread
{
public:

    /**
     * Create a thread that will execute the event loop of \a host.
     */
    HostThread(Host* host);

    /**
     * Destructor, calls abort().
     */
    ~HostThread();

    /**
     * Calls \link Host::quit host->quit() \endlink and waits
     * for the thread to exit.
     */
    void abort();

protected:

    /**
     * Thread main function, calls \link Host::exec host->exec() \endlink
     */
    virtual void run();

private:
    DISABLE_COPY(HostThread);

    Host* m_host;
};

} // namespace pcs

#endif // PIECES_HOST_THREAD_H
