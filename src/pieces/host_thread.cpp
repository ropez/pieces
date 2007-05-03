
#include "Pieces/HostThread"
#include "Pieces/Host"


namespace pcs
{

HostThread::HostThread(Host* host)
: OpenThreads::Thread()
, m_host(host)
{
}


HostThread::~HostThread()
{
    abort();
}


void HostThread::abort()
{
    m_host->quit();
    join();
}


void HostThread::run()
{
    m_host->exec();
}

} // namespace pcs
