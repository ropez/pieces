
#ifndef PIECES_BUFFER_STREAM_H
#define PIECES_BUFFER_STREAM_H

#include "Pieces/DataStream"


namespace Pieces
{
class DataBuffer;


/**
 * \class BufferStream
 * \brief Data stream using an internal buffer.
 *
 * An example of how to write data to a buffer stream:
 * \code
 * DataStream ds;
 * ds << true << 1024 << 3.14159;
 * ByteArray output = ds.data();
 * \endcode
 *
 * An example of how to read the same data:
 * \code
 * DataStream ds(output);
 * bool b;
 * ds >> b;
 * int n;
 * ds >> n;
 * double d;
 * ds >> d;
 * // Also possible to do 'ds >> b >> n >> d' in one line.
 * \endcode
 *
 * \author Robin Pedersem
 */
class BufferStream : public DataStream
{
public:

    /**
     * Create a stream operating on an internal data buffer.
     *
     * This is a typical output stream.
     *
     * All write operations will append data at the end of the internal
     * buffer, which is availible by calling data().
     */
    BufferStream();

    /**
     * Create a stream that starts with the contents of \a data.
     *
     * This is a typical input stream.
     *
     * Read operations will start at the beginning of the data, and will
     * continue where the previous read stopped.
     *
     * Write operations will append data to the internal byte-array which is
     * available by calling data(). The byte-array passed as parameter to this
     * constructor can't be changed.
     */
    explicit BufferStream(const ByteArray& data);

    ~BufferStream();

    /**
     * Returns a copy of the internal byte-array, if the target is a DataBuffer.
     *
     * This array contains everything written using write operations, appended
     * to the byte-array passed to the constructor, if any.
     *
     * It doesn't matter if the data was read or not.
     */
    ByteArray data() const;

private:
    // Disable copy operations
    BufferStream(const BufferStream&);
    BufferStream& operator=(const BufferStream&);

    DataBuffer* m_buf;
};

} // namespace Pieces

#endif // PIECES_BUFFER_STREAM_H
