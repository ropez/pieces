
#ifndef PIECES_BYTE_ARRAY_H
#define PIECES_BYTE_ARRAY_H

namespace Pieces
{

class ByteArrayData;


class ByteArray
{
public:
    ByteArray();
    ByteArray(const char* data, int size);

    ByteArray(const ByteArray& other);
    ByteArray& operator=(const ByteArray& other);

    ~ByteArray();

    int size() const;

    char* data();
    const char* data() const;

private:
    void detach();
    ByteArrayData* d;
};

} // namespace Pieces

#endif // PIECES_BYTE_ARRAY_H
