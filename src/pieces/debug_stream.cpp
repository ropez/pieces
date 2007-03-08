
#include "Pieces/DebugStream"

#include <iostream>
#include <iomanip>


namespace Pieces
{

const int SETWIDTH = 10;
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
    return DebugStream() << std::left << std::setw(SETWIDTH) << "INFO";
}


DebugStream warning()
{
    return DebugStream() << std::left << std::setw(SETWIDTH) << "INFO";
}


DebugStream error()
{
    return DebugStream() << std::left << std::setw(SETWIDTH) << "INFO";
}

} // namespace Pieces
