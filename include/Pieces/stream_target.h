
#ifndef PIECES_STREAM_TARGET_H
#define PIECES_STREAM_TARGET_H

#include "Pieces/ByteArray"


namespace pcs
{

class StreamTarget
{
public:

    /**
     * Virtual destructor to make sure implementations are correctly deleted.
     */
    virtual ~StreamTarget();

    /**
     * Read at most \a maxSize bytes.
     *
     * This function shall never return an empty byte-array, unless \a maxSize
     * is 0, but throw an exception if there is no data to return.
     *
     * It might return a byte-array that is shorter than \a maxSize.
     */
    virtual ByteArray read(size_t maxSize) = 0;

    /**
     * Write data.
     *
     * This function might use a buffer. Must call flush() to guarantee that
     * all data has been written.
     */
    virtual void write(const ByteArray& data) = 0;

    /**
     * Flush all buffered data.
     */
    virtual void flush() = 0;
};

} // namespace pcs

#endif // PIECES_STREAM_TARGET_H
