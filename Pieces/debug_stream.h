
#ifndef PIECES_DEBUG_STREAM_H
#define PIECES_DEBUG_STREAM_H

#include "OpenThreads/Mutex"

#include <ostream>


namespace Pieces
{

class DebugStream
{
public:

    DebugStream();

    DebugStream(DebugStream& other);

    ~DebugStream();

    template<typename T>
    DebugStream& operator<<(T t);

private:

    static OpenThreads::Mutex mutex;

    std::ostream& m_stream;
    bool m_close;
};


DebugStream debug();
DebugStream warning();
DebugStream error();

template<typename T>
DebugStream& DebugStream::operator<<(T t)
{
    m_stream << t;
    return *this;
}

} // namespace Pieces

#endif // PIECES_DEBUG_STREAM_H
