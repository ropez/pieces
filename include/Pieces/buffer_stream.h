/*
    Copyright 2007,2010 The Pieces Team

    This file is part of Pieces.

    Pieces is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Pieces is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
    more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Pieces.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PIECES_BUFFER_STREAM_H
#define PIECES_BUFFER_STREAM_H

#include "Pieces/DataStream"


namespace pcs
{
class DataBuffer;


/**
 * \class BufferStream buffer_stream.h <Pieces/BufferStream>
 * \brief Data stream using an internal buffer.
 *
 * This class provides a DataStream with a DataBuffer as it's target. The
 * buffer stream owns the buffer, and is responsible for releasing resources.
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
 * Using a buffer stream is equivalent to using a DataStream with a DataBuffer:
 *
 * \code
 * // This code using BufferStream:
 * BufferStream bs;
 * bs << values;
 * return bs.data();
 * // is equivalent to this:
 * DataBuffer b;
 * DataStream ds(&b);
 * ds << values;
 * return d.data();
 * \endcode
 *
 * \see DataBuffer, DataStream
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

    /**
     * Destructor.
     *
     * Deletes the buffer.
     */
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
    DISABLE_COPY(BufferStream);

    DataBuffer* m_buf;
};

} // namespace pcs

#endif // PIECES_BUFFER_STREAM_H
