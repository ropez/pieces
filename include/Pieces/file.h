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

#ifndef PIECES_FILE_H
#define PIECES_FILE_H

#include "Pieces/StreamTarget"


namespace pcs
{
class FilePrivate;


class File : public StreamTarget
{
public:
    enum OpenModes
    {
        Read = 0x1,
        Write = 0x2,
        ReadWrite = Read | Write,

        Append = 0x4,
        Truncate = 0x8,
    };

    File(const std::string& name);
    ~File();

    bool open(int modes);
    void close();

    ByteArray read(size_t maxSize);

    void write(const ByteArray& data);

    void flush();

private:
    DISABLE_COPY(File);

    FilePrivate* d;
};

} // namespace Pieces

#endif // PIECES_FILE_H
