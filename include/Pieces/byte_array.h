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

#ifndef PIECES_BYTE_ARRAY_H
#define PIECES_BYTE_ARRAY_H

#include "Pieces/SharedData"
#include "Pieces/SharedDataPointer"

#include <iostream>
#include <climits>


namespace pcs
{

/**
 * \class ByteArray byte_array.h <Pieces/ByteArray>
 * \brief Represents a generic array of bytes.
 *
 * This class preferred to represent binary data instead of the classical pure
 * char pointer. It automatically handles memory allocation and is optimized
 * for passing parameters by value using implicit sharing.
 *
 * Internally, the byte-array preallocates memory to optimize resizing when
 * appending something to the end. In most cases this operation is constant
 * time.
 *
 * \author Robin Pedersen
 */
class ByteArray
{
public:

    /**
     * Type of element, a \em byte is defined as an unsigned char.
     */
    typedef unsigned char byte_t;

    /**
     * Creates an empty byte-array.
     */
    ByteArray();

    /**
     * Creates a byte-array with room for \a size bytes.
     *
     * The data in uninitialized.
     */
    explicit ByteArray(size_t size);

    /**
     * Created a byte-array with \a size bytes, and copies the data pointed to
     * by \a data.
     */
    ByteArray(const void* data, size_t size);

    /**
     * Returns the size of the byte-array, in number of bytes.
     */
    size_t size() const;

    /**
     * Returns the number of bytes allocated. This is always greater or equal
     * to size(). If greates, some memory has been preallocated to optimize
     * insertion at the end.
     */
    size_t allocated() const;

    /**
     * Returns true if size() == 0.
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
    void resize(size_t size);

    /**
     * Returns a pointer to the internal data.
     *
     * This pointer can be used as argument to functions writing to a buffer.
     * \code
     * ByteArray ba(BUFFER_SIZE);
     * fread(ba.data(), ba.size(), 1, file_pointer);
     * \endcode
     *
     * This is the non-const version. If the byte-array contains internal data
     * that is shared with another byte-array (implicit sharing), this will
     * create a deep copy of the internal data before returning a pointer.
     *
     * If you have a non-const byte-array, and you won't change the data, you
     * should use constData() instead. It can give better performance, because
     * it doesn't require a deep copy.
     *
     * \warning You should never store the returned pointer and create a copy
     * of the byte-array, because you will end up having a pointer to shared
     * data. The best way to avoid this is to never use this pointer for
     * anything else than a function parameter.
     *
     * \warning This is not '\\0'-terminated, so it must not be used as a
     * string, decode the byte-array to an std::string instead.
     */
    byte_t* data();

    /**
     * Returns a pointer to the internal data.
     *
     * This is the same as constData(), but is only possible to call on a const
     * byte-array because it has the same name as the non-const version.
     */
    const byte_t* data() const;

    /**
     * Returns a pointer to the internal data.
     *
     * This pointer can be used as arguments to functions reading from a
     * buffer.
     * \code
     * ByteArray ba = getData();
     * fwrite(ba.constData(), ba.size(), 1, file_pointer);
     * \endcode
     *
     * This is the const version. It will never create a deep copy of the data.
     * Since you can not change the data, it doesn't matter that you have a
     * pointer to shared data.
     *
     * If you have a const byte-array, you can use data() instead for
     * convenience. These functions do the same thing. This function is
     * provided so that you can avoid using the non-const version of data() if
     * you have a non-const byte-array.
     *
     * \warning You should never store the returned pointer and call a
     * non-const function on the byte-array, because it may relocate the data,
     * and the location pointed to by this pointer may become invalid. The best
     * way to avoid this is to never use this pointer for anything other than a
     * function parameter.
     *
     * \warning This is not '\\0'-terminated, so it must not be used as a
     * string, decode the byte-array to an std::string instead.
     */
    const byte_t* constData() const;

    /**
     * Returns a reference to the byte at position \a index.
     *
     * This can be used to update individual bytes in the array.
     */
    byte_t& operator[](size_t index);

    /**
     * Returns a const reference to the byte at position \a index.
     *
     * This can be used to read individual bytes from the array.
     */
    const byte_t& operator[](size_t index) const;

    /**
     * Returns a byte-array that contains \a len bytes copied from this
     * byte-array from position \a pos.
     *
     * If \a len is the default value -1, the rest of the array is copied.
     */
    ByteArray middle(size_t pos, size_t len = INT_MAX) const;

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
    ByteArray& append(const void* data, size_t size);

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
    ByteArray& prepend(const void* data, size_t size);

    /**
     * Remove \a n bytes from the start of the byte-array.
     */
    void chopFront(size_t n);

    /**
     * Remove \a n bytes from the end of the byte-array.
     */
    void chopBack(size_t n);

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
        explicit Data(size_t size);

        // Creates a deep copy of the 'size' first bytes at location 'data'.
        Data(const void* data, size_t size);

        // Creates a deep copy (called automatically by SharedDataPointer if needed).
        Data(const Data& other);

        // Creates a deep copy (called automatically by SharedDataPointer if needed).
        Data& operator=(const Data& other);

        // Calculate number of bytes to allocate and allocate uninitialized space.
        // Deletes any old data.
        void allocate(size_t size);

        // The number of bytes allocated.
        size_t allocated;

        // The current size of the byte-array (might be less than or equal to allocated)
        size_t size;

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


/**
 * Returns the result of concatenating the two byte-arrays.
 */
ByteArray operator+(const ByteArray& op1, const ByteArray& op2);


/**
 * Writes a string representing the byte-array to the output stream.
 *
 * This function is meant for debug purposes. The output may not be complete,
 * and it may not contain enough information to regenerate the byte-array.
 * It's meant only to give a human reader some idea of the contents.
 */
std::ostream& operator<<(std::ostream& os, const ByteArray& ba);

} // namespace pcs

#endif // PIECES_BYTE_ARRAY_H
