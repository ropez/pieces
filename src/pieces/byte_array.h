
#ifndef PIECES_BYTE_ARRAY_H
#define PIECES_BYTE_ARRAY_H

#include "SharedData"
#include "SharedDataPointer"

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

    class Data : public SharedData
    {
    public:
        Data();

        Data(const char* data, int size);

        Data(const Data& other);

        Data& operator=(const Data& other);

        ~Data();

        int size;
        char* data;
    };

    SharedDataPointer<Data> d;
};

} // namespace Pieces

#endif // PIECES_BYTE_ARRAY_H
