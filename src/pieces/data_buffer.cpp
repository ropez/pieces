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

#include "Pieces/DataBuffer"
#include "Pieces/IOException"


namespace pcs
{

DataBuffer::DataBuffer()
: m_readPtr(0)
, m_data()
{
}


DataBuffer::DataBuffer(const ByteArray& data)
: m_readPtr(0)
, m_data(data)
{
}


ByteArray DataBuffer::data() const
{
    return m_data;
}


ByteArray DataBuffer::read(size_t maxSize)
{
    // Return empty array if size is 0
    if (maxSize == 0)
    {
        return ByteArray();
    }

    // Check for empty
    if (m_readPtr >= m_data.size())
    {
        throw IOException("Read passed end of buffer");
    }

    // Find size to read
    size_t size = std::min(m_data.size() - m_readPtr, maxSize);

    // Copy data
    ByteArray ba = m_data.middle(m_readPtr, size);
    m_readPtr += size;

    return ba;
}


void DataBuffer::write(const ByteArray& data)
{
    m_data.append(data);
}


void DataBuffer::flush()
{
    // Do nothing
}

} // namespace pcs

