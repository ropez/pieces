
#ifndef PIECES_DEBUG_STREAM_H
#define PIECES_DEBUG_STREAM_H

#include "OpenThreads/Mutex"

#include <sstream>


namespace Pieces
{

class DebugStream : public std::stringstream
{
public:

    DebugStream();

    ~DebugStream();

private:

    // Disabled copy operations
    DebugStream(DebugStream& other);
    DebugStream& operator=(DebugStream&);

    static OpenThreads::Mutex mutex;
};


class _Align
{
public:
    _Align(int c)
    : col(c)
    {
    }

    int col;
};


/**
 * Manipulator for aligning output.
 *
 * Makes output aligned at column \a col.
 * Outputs at least 1, and at most \a col - the number of characters printed
 * on the stream space characters.
 */
inline
_Align align(int col)
{
    return _Align(col);
}

inline
std::ostream& operator<<(std::ostream& os, _Align a)
{
    do
    {
        os << ' ';
    }
    while ((os.tellp() > 0) && (os.tellp() < a.col));

    return os;
}

std::ostream& tid(std::ostream& os);
std::ostream& debug(std::ostream& os);
std::ostream& info(std::ostream& os);
std::ostream& warning(std::ostream& os);
std::ostream& error(std::ostream& os);

#define DEBUG DebugStream() << debug
#define INFO DebugStream() << info
#define WARNING DebugStream() << warning
#define ERROR DebugStream() << error

} // namespace Pieces

#endif // PIECES_DEBUG_STREAM_H
