
#ifndef PIECES_MESSAGE_H
#define PIECES_MESSAGE_H

#include "Pieces/SharedData"
#include "Pieces/SharedDataPointer"
#include "Pieces/PropertyList"
#include "Pieces/DataStream"


namespace Pieces
{


/**
 * \class Message
 * \brief Generic network message class.
 *
 * \author Robin Pedersen
 */
class Message
{
public:
    Message();
    ~Message();

    explicit Message(int messageType);
    Message(int messageType, const PropertyList& properties);

    Message(const Message& other);
    Message& operator=(const Message& other);

    /**
     * Set type to NO_MESSAGE_TYPE and remove all properties.
     */
    void clear();

    void setMessageType(int messageType);
    int getMessageType() const;

    void setProperties(const PropertyList& properties);
    PropertyList getProperties() const;


    /**
     * Add or update a property, converted from T.
     *
     * Equivalent to:
     * \code
     * PropertyList p = getProperties();
     * p.set<T>(property, value);
     * setProperties(p);
     * \endcode
     */
    template<typename T>
    void set(int property, const T& value);

    /**
     * Get a property value, converted to T.
     *
     * Equivalent to:
     * \code
     * PropertyList p = getProperties();
     * p.get<T>(property, defval);
     * \endcode
     */
    template<typename T>
    T get(int property, const T& defval = T()) const;

private:
    class Data : public SharedData
    {
    public:
        Data();

        Data(const Data& other);
        Data& operator=(const Data& other);

        int type;
        PropertyList properties;
    };

    SharedDataPointer<Data> d;
};

DataStream& operator<<(DataStream& ds, const Message& msg);
DataStream& operator>>(DataStream& ds, Message& msg);


template<typename T>
void Message::set(int property, const T& value)
{
    d->properties.set<T>(property, value);
}

template<typename T>
T Message::get(int property, const T& defval) const
{
    return d->properties.get<T>(property, defval);
}

} // namespace Pieces

#endif // PIECES_MESSAGE_H
