
#ifndef PIECES_BYTE_ARRAY_H
#define PIECES_BYTE_ARRAY_H

namespace Pieces
{

class ByteArray
{
public:
    ByteArray();
    ByteArray(const char* data, int size);

    int size() const;

    char* data();
    const char* data() const;

private:
    int m_size;
    char* m_data;
};

} // namespace Pieces

#endif // PIECES_BYTE_ARRAY_H
