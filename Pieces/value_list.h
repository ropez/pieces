#ifndef PIECES_VALUE_LIST_H
#define PIECES_VALUE_LIST_H

#include "Pieces/ByteArray"
#include "Pieces/DataStream"
#include "Pieces/SharedData"
#include "Pieces/SharedDataPointer"

#include <vector>


namespace Pieces
{


/**
 * \class ValueList
 * \brief An indexed-based list of values.
 *
 * A value-list contains an index-based list of values, stored as generic
 * binary data using ByteArray.
 *
 * The get() and set() functions provide a simple way to convert values to
 * and from any type. To use get/set with a custom data type, the class must
 * have a default and copy constructor, and there must be encode and decode
 * functions for the data type.
 *
 * The Pieces framework provides get/set functions for all basic built-in types
 * and for all value-based Pieces classes including ValueList and PropertyList
 * itself.
 *
 * \note About string constant values.
 * It's legal to use a string constant as a value (e.g. add("abc")).
 * To read this value use std::string (e.g. get<std::string>(0)).
 *
 * \see PropertyList, ByteArray, DataStream
 * \author Robin Pedersen
 */
class ValueList
{
public:

    /**
     * Constructor that creates an empty value-list.
     */
    ValueList();

    /**
     * Destructor that cleans up all resources.
     */
    ~ValueList();

    /**
     * Remove all values.
     */
    void clear();

    /**
     * Returns the number of values.
     */
    int size() const;

    /**
     * Returns true if size() == 0.
     */
    bool isEmpty() const;

    /**
     * Add a value to the end of the list.
     *
     * Updates the value-list by adding \a value at the end of the list.
     * The index of \a value will be equal to the size() before the
     * call to this function.
     */
    ValueList& addValue(const ByteArray& value);

    /**
     * Returns the value at the given index.
     *
     * The \a index must be between 0 (inclusive) and size() (exclusive).
     */
    ByteArray getValue(int index) const;

    /**
     * Add a value to the end of the list, converted from T.
     *
     * Updates the value-list by adding \a value, converted to T using the
     * encode() function for T, at the end of the list.
     *
     * \pre There must be a function called encode that converts a T to a
     * ByteArrray.
     */
    template<typename T>
    ValueList& add(const T& value);

    /**
     * Returns the value at the given index, converted to T.
     *
     * The value is converted to T using the decode() function for T.
     *
     * \pre The type T must have a default and copy contructor and there must
     * be a function called decode that converts a ByteArray to T.
     */
    template<typename T>
    T get(int index) const;

    /** \warning This typedef may be removed. */
    typedef std::vector<ByteArray> list_t;

    /** \warning This function may be removed. */
    list_t::const_iterator begin() const;

    /** \warning This function may be removed. */
    list_t::const_iterator end() const;

private:
    class Data : public SharedData
    {
    public:
        Data();
        Data(const Data& other);

        list_t values;
    };

    SharedDataPointer<Data> d;
};


/**
 * Writes a string representing the value-list to the output stream.
 *
 * This function is meant for debug purposes. The output may not be complete,
 * and it may not contain enough information to regenerate the property-list.
 * It's meant only to give a human reader some idea of the contents.
 */
std::ostream& operator<<(std::ostream& os, const ValueList& l);


/**
 * Write value-list to a data stream.
 *
 * Writes a binary representation of the value-list \a l to the data stream
 * \a ds, and returns \a ds.
 *
 * The value-list can be read back using the input stream operator.
 */
DataStream& operator<<(DataStream& ds, const ValueList& l);


/**
 * Reads a value-list from a data stream.
 *
 * Reads the binary representation of a value-list, and makes the
 * property-list referenced by \a l equal to the stored list.
 *
 * The data stream must contain a value-list stored with the output
 * operator.
 */
DataStream& operator>>(DataStream& ds, ValueList& l);


/**
 * Convert a value-list to a byte-array.
 *
 * Stores a binary representation of the value-list \a l in the
 * byte-array referenced by \a ba.
 */
void encode(ByteArray& ba, const ValueList& l);


/**
 * Convert a byte-array to a value-list.
 *
 * Creates a value-list by reading the binary representation stored in
 * \a ba, and makes the value-list referenced by \a l equal to the stored
 * list.
 */
void decode(const ByteArray& ba, ValueList& l);

template<typename T>
ValueList& ValueList::add(const T& value)
{
    ByteArray ba;
    encode(ba, value);
    return addValue(ba);
}

template<typename T>
T ValueList::get(int index) const
{
    ByteArray ba = getValue(index);
    T result;
    decode(ba, result);
    return result;
}

} // namespace Pieces

#endif // PIECES_VALUE_LIST_H
