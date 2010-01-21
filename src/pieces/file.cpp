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

#include "Pieces/File"
#include "Pieces/IOException"
#include "Pieces/TimeoutException"
#include "Pieces/Debug"

#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>


namespace pcs
{

class FilePrivate
{
public:
    FilePrivate();

    int fd;
    ByteArray writebuf;

    std::string name;
};


FilePrivate::FilePrivate()
: fd(-1)
, name()
{
}


File::File(const std::string& name)
: d(new FilePrivate)
{
    d->name = name;
}


File::~File()
{
    close();
    delete d;
}


bool File::open(int modes)
{
    // Convert modes
    int mode = 0;
    mode |= (modes & Read) ? O_RDONLY : 0;
    mode |= (modes & Write) ? O_WRONLY | O_CREAT : 0;
    mode |= (modes & Append) ? O_APPEND : 0;
    mode |= (modes & Truncate) ? O_TRUNC : 0;

    // Open file
    d->fd = ::open(d->name.c_str(), mode, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);

    // Error handling
    if (d->fd < 0)
    {
        switch (errno)
        {
        case ENOENT: // File not found
        case ENOTDIR: // A path component was not a directory
        case EEXIST: // File exists, and we wanted to create a new file
            // This is not an exception
            return false;
        case EACCES:
            // TODO: Special access denied exception
        default:
            // Error
            throw IOException("File::open", strerror(errno));
        }
    }

    return true;
}


void File::close()
{
    if (d->fd != -1)
    {
        try
        {
            flush();
        }
        catch (const Exception& e)
        {
            PWARNING << e;
        }

        ::close(d->fd);
        d->fd = -1;
    }
}


ByteArray File::read(size_t maxSize)
{
    ByteArray ba(maxSize);

    // Return empty array if size is 0
    if (maxSize == 0)
    {
        return ba;
    }

    // Read from file
    ssize_t size = ::read(d->fd, ba.data(), ba.size());

    // Check for errors
    if (size < 0)
    {
        switch (errno)
        {
        case EAGAIN:
        case ETIMEDOUT:
            throw TimeoutException("File::read", strerror(errno));
        default:
            throw IOException("File::read", strerror(errno));
        }
    }

    // If size is 0, means end of file
    if (size == 0)
    {
        throw IOException("TCPSocket::read", "End of file");
    }

    // Return a byte-array of the actual read size
    return ByteArray(ba.constData(), size);
}


void File::write(const ByteArray& data)
{
    d->writebuf.append(data);
}


void File::flush()
{
    size_t written = 0;
    while (written < d->writebuf.size())
    {
        ssize_t size = ::write(d->fd, d->writebuf.data(), d->writebuf.size());

        if (size < 0)
        {
            switch (errno)
            {
            case EAGAIN:
            case ETIMEDOUT:
                throw TimeoutException("File::flush", strerror(errno));
            default:
                throw IOException("File::flush", strerror(errno));
            }
        }
        written += size;
    }
    d->writebuf.clear();
}

}
