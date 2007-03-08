
#ifndef PIECES_DEBUG_STREAM_H
#define PIECES_DEBUG_STREAM_H

#include "OpenThreads/Mutex"

#include <sstream>


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

    // Disabled assignment operator
    DebugStream& operator=(DebugStream&);

    static OpenThreads::Mutex mutex;

    std::auto_ptr<std::stringstream> m_ss;
    std::ostream& m_stream;
};


DebugStream debug();
DebugStream warning();
DebugStream error();


// Alignment manipulator
class AlignmentManipulator
{
public:
    AlignmentManipulator(int w)
    : width(w)
    {
    }

    int width;
};

inline AlignmentManipulator align(int width)
{
    return AlignmentManipulator(width);
}

template<typename T> inline
DebugStream& DebugStream::operator<<(T t)
{
    if (m_ss.get() != 0)
    {
        *m_ss << t;
    }
    return *this;
}


template<> inline
DebugStream& DebugStream::operator<< <AlignmentManipulator>(AlignmentManipulator t)
{
    if (m_ss.get() != 0)
    {
        do
        {
            *m_ss << ' ';
        }
        while (m_ss->tellp() < t.width);
    }

    return *this;
}

} // namespace Pieces

#endif // PIECES_DEBUG_STREAM_H
