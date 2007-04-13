
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

    enum MessageFlags
    {
        FL_PERMANENT = 0x01
    };

    Message();
    ~Message();

    explicit Message(int messageType, flags_t flags = 0);

    Message(const Message& other);
    Message& operator=(const Message& other);

    /**
     * Set type to NO_MESSAGE_TYPE and remove all properties.
     */
    void clear();

    void setMessageType(int messageType);
    int getMessageType() const;

    void setFlags(flags_t flags);
    flags_t getFlags();

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
        flags_t flags;
        PropertyList properties;
    };

    SharedDataPointer<Data> d;
};

DataStream& operator<<(DataStream& ds, const Message& msg);
DataStream& operator>>(DataStream& ds, Message& msg);


typedef unsigned long msgid_t;
typedef std::pair<msgid_t, Message> msgpair_t;


class MessageIdLess
{
public:
    bool operator()(const msgid_t& idl, msgid_t idr)
    {
        return (idl < idr);
    }

    bool operator()(const msgpair_t& msg, msgid_t id)
    {
        return operator()(msg.first, id);
    }

    bool operator()(msgid_t id, const msgpair_t& msg)
    {
        return operator()(id, msg.first);
    }

    bool operator()(const msgpair_t& msgl, const msgpair_t& msgr)
    {
        return operator()(msgl.first, msgr.first);
    }
};


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
