
#ifndef PIECES_BYTE_ARRAY_H
#define PIECES_BYTE_ARRAY_H

#include "SharedData"
#include "SharedDataPointer"

#include <iostream>


namespace Pieces
{

typedef unsigned char byte_t;

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
    ByteArray(const void* data, int size);

    /**
     * Returns the size of the byte-array.
     */
    int size() const;

    /**
     * Returns true is size() == 0.
     */
    bool isEmpty() const;

    /**
     * Remove contents.
     */
    void clear();

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
    byte_t* data();

    /**
     * Returns a pointer to the internal data.
     */
    const byte_t* data() const;

    /**
     * Returns a pointer to the internal data.
     */
    const byte_t* constData() const;

    /**
     * Returns a reference to the byte at position \a index.
     */
    byte_t& operator[](int index);

    /**
     * Returns a const reference to the byte at position \a index.
     */
    const byte_t& operator[](int index) const;

    /**
     * Returns a byte-array that contains \a len bytes copied from this
     * byte-array from position \a pos.
     *
     * If \a len is the default value -1, the rest of the array is copied.
     */
    ByteArray middle(int pos, int len = -1) const;

    /**
     * Returns a byte-array that contains \a len bytes copied from the start
     * of this byte-array.
     *
     * Same as middle(0, len);
     */
    ByteArray left(int len) const;

    /**
     * Returns a byte-array that contains \a len bytes copied from the end
     * of this byte-array.
     *
     * Same as middle(size() - len, len);
     */
    ByteArray right(int len) const;

    /**
     * Append \a byte to this byte-array.
     */
    ByteArray& append(byte_t byte);

    /**
     * Append \a other to this byte-array.
     */
    ByteArray& append(const ByteArray& other);

    /**
     * Append \a data to this byte-array.
     */
    ByteArray& append(const void* data, int size);

    /**
     * Prepend \a byte to this byte-array.
     */
    ByteArray& prepend(byte_t byte);

    /**
     * Prepend \a other to this byte-array.
     */
    ByteArray& prepend(const ByteArray& other);

    /**
     * Prepend \a data to this byte-array.
     */
    ByteArray& prepend(const void* data, int size);

    /**
     * Remove \a n bytes from the start of the byte-array.
     */
    void chopFront(int n);

    /**
     * Remove \a n bytes from the end of the byte-array.
     */
    void chopBack(int n);

    /**
     * Append \a other to this byte-array.
     */
    ByteArray& operator+=(const ByteArray& other);

private:

    class Data : public SharedData
    {
    public:

        // Creates an empty array
        Data();

        // Creates a 'size' element array
        explicit Data(int size);

        // Creates a deep copy of the 'size' first bytes at location 'data'.
        Data(const void* data, int size);

        // Creates a deep copy (called automatically by SharedDataPointer if needed).
        Data(const Data& other);

        // Creates a deep copy (called automatically by SharedDataPointer if needed).
        Data& operator=(const Data& other);

        // The number of bytes allocated.
        int size;

        // Pointer to allocated data.
        byte_t* data;

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

std::ostream& operator<<(std::ostream& os, const ByteArray& ba);

} // namespace Pieces

#endif // PIECES_BYTE_ARRAY_H
