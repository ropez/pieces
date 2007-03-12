
#include "Pieces/DebugStream"
#include "OpenThreads/Thread"

#include <sstream>
#include <iostream>
#include <iomanip>


namespace Pieces
{

OpenThreads::Mutex DebugStream::mutex;


DebugStream::DebugStream()
: std::stringstream()
{
}


DebugStream::~DebugStream()
{
    mutex.lock();
    std::cout << str() << std::endl;
    mutex.unlock();
}


std::ostream& tid(std::ostream& os)
{
    OpenThreads::Thread* thread = OpenThreads::Thread::CurrentThread();
    int threadId = (thread != 0) ? thread->getThreadId() : 0;

    return os << "[T:" << threadId << "]" << align(7);
}


std::ostream& debug(std::ostream& os)
{
    return os << "DEBUG" << align(10);
}


std::ostream& info(std::ostream& os)
{
    return os << "INFO" << align(10);
}


std::ostream& warning(std::ostream& os)
{
    return os << "WARNING" << align(10);
}


std::ostream& error(std::ostream& os)
{
    return os << "ERROR" << align(10);
}

} // namespace Pieces
