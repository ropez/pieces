
#ifndef PIECES_HOST_THREAD_H
#define PIECES_HOST_THREAD_H

#include "Pieces/global"
#include "OpenThreads/Thread"


namespace pcs
{
class Host;


/**
 * \class HostThread
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
    HostThread(Host* host);
    ~HostThread();

    void abort();

protected:
    virtual void run();

private:
    DISABLE_COPY(HostThread);

    Host* m_host;
};

} // namespace pcs

#endif // PIECES_HOST_THREAD_H
