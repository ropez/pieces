
#include "Pieces/DebugStream"
#include "OpenThreads/Thread"

#include <sstream>
#include <iostream>
#include <iomanip>


namespace Pieces
{

namespace
{
const int SETWIDTH = 10;

DebugStream thread()
{
    OpenThreads::Thread* thread = OpenThreads::Thread::CurrentThread();
    int threadId = (thread != 0) ? thread->getThreadId() : 0;

    std::stringstream ss;
    ss << "[T:" << threadId << "]";

    return DebugStream() << std::left << std::setw(7) << ss.str();
}

}

OpenThreads::Mutex DebugStream::mutex;


DebugStream::DebugStream()
: m_stream(std::cout)
, m_close(true)
{
    mutex.lock();
}


DebugStream::DebugStream(DebugStream& other)
: m_stream(other.m_stream)
, m_close(other.m_close)
{
    other.m_close = false;
}


DebugStream::~DebugStream()
{
    if (m_close)
    {
        std::cout << std::endl;
        mutex.unlock();
    }
}


DebugStream debug()
{
    return thread() << std::left << std::setw(SETWIDTH) << "INFO";
}


DebugStream warning()
{
    return thread() << std::left << std::setw(SETWIDTH) << "INFO";
}


DebugStream error()
{
    return thread() << std::left << std::setw(SETWIDTH) << "INFO";
}

} // namespace Pieces
