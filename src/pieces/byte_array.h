
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
     * Creates a byte-array with room for \a size bytes.
     *
     * The data in uninitialized.
     */
    explicit ByteArray(int size);

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
     * Returns true is size() == 0.
     */
    bool isEmpty() const;

    /**
     * Resize the array to \a size bytes.
     *
     * If \a size is smaller than the original size, the new array will contain
     * the \a size first bytes of the original. If \a size is larger than the
     * original size, the first original size bytes of the array will constain
     * the original contents, and the rest is uninitialized.
     */
    void resize(int size);

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

        // Creates a 'size' element array
        explicit Data(int size);

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

/**
 * Comparison operator, returns true if the size and conents of the two
 * byte-arrays are equal, otherwise false.
 */
bool operator==(const ByteArray& op1, const ByteArray& op2);

/**
 * Comparison operator, returns false if the size and conents of the two
 * byte-arrays are equal, otherwise true.
 */
bool operator!=(const ByteArray& op1, const ByteArray& op2);

ByteArray operator+(const ByteArray& op1, const ByteArray& op2);

} // namespace Pieces

#endif // PIECES_BYTE_ARRAY_H
