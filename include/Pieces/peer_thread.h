
#ifndef PIECES_PEER_THREAD_H
#define PIECES_PEER_THREAD_H

#include "Pieces/global"
#include "OpenThreads/Thread"


namespace pcs
{
class Peer;


/**
 * \class PeerThread
 * \brief Thread that executes a peer.
 *
 * This is a convenience class that can be used to run a peer in a background
 * thread.
 *
 * \author Robin Pedersen
 */
class PeerThread : public OpenThreads::Thread
{
public:
    PeerThread(Peer* peer);
    ~PeerThread();

    void abort();

protected:
    virtual void run();

private:
    DISABLE_COPY(PeerThread);

    Peer* m_peer;
};

} // namespace pcs

#endif // PIECES_HOST_THREAD_H
