
#ifndef PIECES_FILE_H
#define PIECES_FILE_H

#include "Pieces/StreamTarget"


namespace Pieces
{
class FilePrivate;


/**
 * \class File
 * \brief OS independant file IO.
 *
 * \author Robin Pedersen
 */
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
