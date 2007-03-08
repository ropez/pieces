
#include "Pieces/DebugStream"
#include "OpenThreads/Thread"

#include <sstream>
#include <iostream>
#include <iomanip>


namespace Pieces
{

namespace
{

DebugStream thread()
{
    OpenThreads::Thread* thread = OpenThreads::Thread::CurrentThread();
    int threadId = (thread != 0) ? thread->getThreadId() : 0;

    return DebugStream() << "[T:" << threadId << "]" << align(7);
}

}

OpenThreads::Mutex DebugStream::mutex;


DebugStream::DebugStream()
: m_ss(new std::stringstream)
, m_stream(std::cout)
{
    mutex.lock();
}


DebugStream::DebugStream(DebugStream& other)
: m_ss(other.m_ss)
, m_stream(other.m_stream)
{
}


DebugStream::~DebugStream()
{
    if (m_ss.get() != 0)
    {
        m_stream << m_ss->str() << std::endl;
        mutex.unlock();
    }
}


DebugStream debug()
{
    return thread() << "INFO" << align(15);
}


DebugStream warning()
{
    return thread() << "INFO" << align(15);
}


DebugStream error()
{
    return thread() << "INFO" << align(15);
}

} // namespace Pieces
