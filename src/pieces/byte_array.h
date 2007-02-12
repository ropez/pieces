
#ifndef PIECES_BYTE_ARRAY_H
#define PIECES_BYTE_ARRAY_H

#include "SharedData"
#include "SharedDataPointer"

namespace Pieces
{

/**
 * Represents a generic array of bytes.
 *
 * This class preferred to represent binary data instead of the classical pure
 * char pointer. It automatically handles memory allocation and is optimized
 * for passing parameters by value using implicit sharing.
 */
class ByteArray
{
public:

    /**
     * Creates an empty byte-array.
     */
    ByteArray();

    /**
     * Created a byte-array with \a size bytes, and copies the data pointed to
     * by \a data.
     */
    ByteArray(const char* data, int size);

    /**
     * Returns the size of the byte-array.
     */
    int size() const;

    /**
     * Returns a pointer to the internal data.
     */
    char* data();

    /**
     * Returns a pointer to the internal data.
     */
    const char* data() const;

    /**
     * Returns a reference to the byte at position \a index.
     */
    char& operator[](int index);

    /**
     * Returns a const reference to the byte at position \a index.
     */
    const char& operator[](int index) const;

private:

    class Data : public SharedData
    {
    public:

        // Creates an empty array
        Data();

        // Creates a deep copy of the 'size' first bytes at location 'data'.
        Data(const char* data, int size);

        // Creates a deep copy (called automatically by SharedDataPointer if needed).
        Data(const Data& other);

        // Creates a deep copy (called automatically by SharedDataPointer if needed).
        Data& operator=(const Data& other);

        // The number of bytes allocated.
        int size;

        // Pointer to allocated data.
        char* data;

    protected:

        // Make data pointer able to call destructor.
        friend class SharedDataPointer<Data>;

        // Protected to prevent stack allocation.
        ~Data();
    };

    SharedDataPointer<Data> d;
};

} // namespace Pieces

#endif // PIECES_BYTE_ARRAY_H
