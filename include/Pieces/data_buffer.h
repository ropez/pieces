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

#ifndef PIECES_DATA_BUFFER_H
#define PIECES_DATA_BUFFER_H

#include "Pieces/StreamTarget"


namespace pcs
{


/**
 * \class DataBuffer data_buffer.h <Pieces/DataBuffer>
 * \brief An internal data buffer.
 *
 * A data-buffer is a stream target that operates on an internal byte-array.
 *
 * A write operation always adds to the end of the byte-array, and a read
 * operation starts from the beginning and continues where the previous read
 * operation stopped until the end is reached.
 *
 * A DataStream using a data-buffer is typically used as either an input or
 * an output stream, but it's perfectly possible to do both on the same stream.
 * Note however that if you have a loop where you write to and read from the
 * same data stream, it will keep growing forever. The read operations doesn't
 * remove any data from the beginning of the byte-array.
 *
 * \see BufferStream
 * \author Robin Pedersen
 */
class DataBuffer : public StreamTarget
{
public:

    /**
     * Create an empty buffer.
     */
    DataBuffer();

    /**
     * Create a buffer starting with the contents of \a data.
     */
    DataBuffer(const ByteArray& data);

    /**
     * Returns the data currently in the buffer.
     *
     * This also includes data previously returned by read().
     */
    ByteArray data() const;

    /**
     * Returns at most \a maxSize bytes from the internal buffer, and increments
     * the internal read pointer accordingly.
     */
    virtual ByteArray read(size_t maxSize);

    /**
     * Appends \a data to the end of the internal buffer.
     */
    virtual void write(const ByteArray& data);

    /**
     * Does nothing.
     */
    virtual void flush();

private:
    DISABLE_COPY(DataBuffer);

    // Current read location
    size_t m_readPtr;

    // Internal data
    ByteArray m_data;
};

} // namespace pcs

#endif // PIECES_DATA_BUFFER_H
