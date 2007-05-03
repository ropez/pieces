
#include "Pieces/PeerThread"
#include "Pieces/Peer"


namespace pcs
{

PeerThread::PeerThread(Peer* peer)
: OpenThreads::Thread()
, m_peer(peer)
{
}


PeerThread::~PeerThread()
{
    abort();
}


void PeerThread::abort()
{
    m_peer->quit();
    join();
}


void PeerThread::run()
{
    m_peer->exec();
}

} // namespace pcs
