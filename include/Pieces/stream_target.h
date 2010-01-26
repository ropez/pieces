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

#ifndef PIECES_STREAM_TARGET_H
#define PIECES_STREAM_TARGET_H

#include "Pieces/ByteArray"


namespace pcs
{


/**
 * \class StreamTarget stream_target.h <Pieces/StreamTarget>
 * \brief Base class for stream targets.
 *
 * This is a pure abstract interface that is common for classes used by
 * DataStream to read and write data.
 *
 * \author Robin Pedersen
 */
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
