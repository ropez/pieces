
#ifndef PIECES_DEBUG_STREAM_H
#define PIECES_DEBUG_STREAM_H

#include "OpenThreads/Mutex"

#include <sstream>


namespace Pieces
{


/**
 * \class DebugStream
 * \brief Debug output stream.
 *
 * This class provides a standard debug output stream with automatic
 * synchronization between threads. Everything that is stream is buffered
 * in the stringstream (base class), and is finally printed to std::cout
 * in the destructor.
 *
 * It uses a static Mutex that to synchronize the output in the destructor.
 *
 * When used with manipulators align(), tid(), debug(), info(), warning()
 * and error(), it also provides a project-wide default way to print debug
 * output.
 *
 * \author Robin Pedersen
 */
class DebugStream : public std::stringstream
{
public:

    /**
     * Constructor creates a standard stringstream.
     */
    DebugStream();

    /**
     * Locks the mutex, and prints all output to std::cout, followed by a
     * std::endl.
     */
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
 *
 * \relates DebugStream
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

/**
 * Prints the current thread id, and aligns for next output.
 *
 * \relates DebugStream
 */
std::ostream& tid(std::ostream& os);

/**
 * Prints thread id, then "DEBUG", and aligns for next output.
 *
 * \relates DebugStream
 */
std::ostream& debug(std::ostream& os);

/**
 * Prints thread id, then "INFO", and aligns for next output.
 *
 * \relates DebugStream
 */
std::ostream& info(std::ostream& os);

/**
 * Prints thread id, then "WARNING", and aligns for next output.
 *
 * \relates DebugStream
 */
std::ostream& warning(std::ostream& os);

/**
 * Prints thread id, then "ERROR", and aligns for next output.
 *
 * \relates DebugStream
 */
std::ostream& error(std::ostream& os);

#define PDEBUG Pieces::DebugStream() << Pieces::debug
#define PINFO Pieces::DebugStream() << Pieces::info
#define PWARNING Pieces::DebugStream() << Pieces::warning
#define PERROR Pieces::DebugStream() << Pieces::error

} // namespace Pieces

#endif // PIECES_DEBUG_STREAM_H
