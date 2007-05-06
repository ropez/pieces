
#ifndef PIECES_PROPERTY_LIST_H
#define PIECES_PROPERTY_LIST_H

#include "Pieces/ByteArray"
#include "Pieces/SharedData"
#include "Pieces/SharedDataPointer"

#include <map>


namespace pcs
{
class DataStream;


/**
 * \class PropertyList property_list.h <Pieces/PropertyList>
 * \brief A collection of key/value pairs.
 *
 * A property list contains a collection of key/value pairs where the keys are
 * integers, and the values are stored as generic binary data using ByteArray.
 *
 * The get() and set() functions provide a simple way to convert property
 * values to and from any type. To use get/set with a custom data type, the
 * class must have a default and copy constructor, and there must be encode
 * and decode functions for the data type.
 *
 * The Pieces framework provides get/set functions for all basic built-in types
 * and for all value-based Pieces classes including ValueList and PropertyList
 * itself.
 *
 * \note About string constant values.
 * It's legal to use a string constant as property value (e.g. set(KEY, "abc")).
 * To read this value use std::string (e.g. get<std::string>(KEY)).
 *
 * \see ValueList, ByteArray, DataStream
 * \author Robin Pedersen
 */
class PropertyList
{
public:

    /**
     * Constructor that creates an empty property-list.
     */
    PropertyList();

    /**
     * Destructor that cleans up all resources.
     */
    ~PropertyList();

    /**
     * Remove all properties.
     */
    void clear();

    /**
     * Returns the number of properties.
     */
    int size() const;

    /**
     * Returns true if size() == 0.
     */
    bool isEmpty() const;

    /**
     * Add or update a property.
     *
     * Updates the property-list by inserting a property with key \a property,
     * or replacing the old value with the contents of \a value.
     */
    PropertyList& setProperty(int property, const ByteArray& value);

    /**
     * Get a property value.
     *
     * This function returns the value of the property with the given \a key.
     * If no property with the key exits, it returns \a defval.
     */
    ByteArray getProperty(int property, const ByteArray& defval = ByteArray()) const;

    /**
     * Add or update a property, converted from T.
     *
     * Updates the property-list by inserting a property with key \a property,
     * or replacing the old value with the contents of \a value, converted to
     * a ByteArray using the encode() function for T.
     *
     * \pre There must be a function called encode that converts a T to a
     * ByteArrray.
     */
    template<typename T>
    PropertyList& set(int property, const T& value);

    /**
     * Get a property value, converted to T.
     *
     * This function returns the value of the property with the given \a key,
     * converted to T using the decode() function for T. If no property with
     * the key exits, it returns \a defval.
     *
     * \pre The type T must have a default and copy contructor and there must
     * be a function called decode that converts a ByteArray to T.
     */
    template<typename T>
    T get(int property, const T& defval = T()) const;

    /** \warning This typedef may be removed. */
    typedef std::map<int, ByteArray> map_t;

    /** \warning This function may be removed. */
    map_t::const_iterator begin() const;

    /** \warning This function may be removed. */
    map_t::const_iterator end() const;

private:
    class Data : public SharedData
    {
    public:
        Data();
        Data(const Data& other);

        map_t properties;
    };

    SharedDataPointer<Data> d;
};


/**
 * Writes a string representing the property-list to the output stream.
 *
 * This function is meant for debug purposes. The output may not be complete,
 * and it may not contain enough information to regenerate the property-list.
 * It's meant only to give a human reader some idea of the contents.
 */
std::ostream& operator<<(std::ostream& os, const PropertyList& p);


/**
 * Write property-list to a data stream.
 *
 * Writes a binary representation of the property-list \a p to the data stream
 * \a ds, and returns \a ds.
 *
 * The property-list can be read back using the input stream operator.
 */
DataStream& operator<<(DataStream& ds, const PropertyList& p);


/**
 * Reads a property-list from a data stream.
 *
 * Reads the binary representation of a property-list, and makes the
 * property-list referenced by \a p equal to the stored list.
 *
 * The data stream must contain a property-list stored with the output
 * operator.
 */
DataStream& operator>>(DataStream& ds, PropertyList& p);


/**
 * Convert a property-list to a byte-array.
 *
 * Stores a binary representation of the property list \a p in the
 * byte-array referenced by \a ba.
 */
void encode(ByteArray& ba, const PropertyList& p);


/**
 * Convert a byte-array to a property-list.
 *
 * Creates a property-list by reading the binary representation stored in
 * \a ba, and makes the property-list referenced by \a p equal to the stored
 * list.
 */
void decode(const ByteArray& ba, PropertyList& p);


template<typename T>
PropertyList& PropertyList::set(int property, const T& value)
{
    ByteArray ba;
    encode(ba, value);
    return setProperty(property, ba);
}


template<typename T>
T PropertyList::get(int property, const T& defval) const
{
    // Lookup the value in the map.
    map_t::const_iterator it = d->properties.find(property);

    // See if it was found.
    if (it != d->properties.end())
    {
        T result;
        decode(it->second, result);
        return result;
    }
    else
    {
        return defval;
    }
}

} // namespace pcs

#endif // PIECES_PROPERTY_LIST_H
