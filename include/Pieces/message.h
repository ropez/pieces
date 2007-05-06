
#ifndef PIECES_MESSAGE_H
#define PIECES_MESSAGE_H

#include "Pieces/SharedData"
#include "Pieces/SharedDataPointer"
#include "Pieces/PropertyList"
#include "Pieces/DataStream"


namespace pcs
{


/**
 * \class Message message.h <Pieces/Message>
 * \brief Generic network message class.
 *
 * This class defines the message type used by the Pieces message system. All
 * messages sent between a Pieces host and connected peers are represented as
 * instances of this class.
 *
 * Every message has a 32-bit message type parameter, represented as an integer,
 * or more likely a named constant or enum value. Message types below 1000 are
 * reserved for use by Pieces internally. Message types above 1000 are available
 * for user-defined messages.
 *
 * A message contains a set of flags that can alter the default behaviour of the
 * message system, these are defined in MessageFlags.
 *
 * All other data must be represented as generic key/value properties, handled
 * internally as a pcs::PropertyList. The keys are similar to the message type.
 * Keys below 1000 are reserved for internal use. The rest is available for user-
 * defined properties.
 *
 * Property values are represented internally as pcs::ByteArray, but the get
 * and set functions can be used to implicitly convert to and from any data type,
 * assuming that there are \em encode and \em decode functions for that type.
 * (see \ref data_encoding).
 *
 * This class is implicitly shared (see \ref implicit_sharing).
 *
 * \author Robin Pedersen
 */
class Message
{
public:

    /**
     * Message flags.
     */
    enum MessageFlags
    {
        /**
         * When set, the message will be stored, and sent on all future connections.
         *
         * This is mostly useful when a host is sending messages that must be
         * received by all peers, even if they haven't connected yet. An example
         * is when sending create messages for game objects.
         */
        FL_PERMANENT = 0x01
    };

    /**
     * Create an uninitialized message (NO_MESSAGE_TYPE).
     *
     * Normally when creating messages, another constructor should be used. This
     * constructor is used when creating a message object that is later read from a
     * stream e.g:
     *
     * \code
     * Message msg;
     * ds >> msg;
     * \endcode
     */
    Message();

    /**
     * Destructor.
     */
    ~Message();

    /**
     * Create a message of a given \a messageType, optinally with a set of \a flags.
     */
    explicit Message(int messageType, flags_t flags = 0);

    /**
     * Copy constructor.
     */
    Message(const Message& other);

    /**
     * Assignment operator.
     */
    Message& operator=(const Message& other);

    /**
     * Set type to NO_MESSAGE_TYPE, reset all flags and remove all properties.
     */
    void clear();

    /**
     * Set message type to \a messageType.
     */
    void setMessageType(int messageType);

    /**
     * Returns the message type.
     */
    int getMessageType() const;

    /**
     * Replace this message's flags with \a flags.
     */
    void setFlags(flags_t flags);

    /**
     * Returns this message's flags.
     */
    flags_t getFlags() const;

    /**
     * Replace all properties of this message with the property list
     * \a properties.
     *
     * Because of implicit sharing, this is actually a very fast operation.
     * Using code like this is actuall no problem, even if the message contains
     * a huge number of properties:
     * \code
     * PropertyList pl = message.getProperties();
     * pl.set(SOME_PROPERTY, value);
     * message.setProperties(pl);
     * \endcode
     *
     * However, it's simpler to just write this equivalent code:
     * \code
     * message.set(SOME_PROPERTY, value);
     * \endcode
     */
    void setProperties(const PropertyList& properties);

    /**
     * Returns all properties stored in this message.
     *
     * \see setProperties().
     */
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


/**
 * Write the message \a msg to the data-stream \a ds.
 *
 * \relates Message
 */
DataStream& operator<<(DataStream& ds, const Message& msg);

/**
 * Read the message \a msg from the data-stream \a ds.
 *
 * \relates Message
 */
DataStream& operator>>(DataStream& ds, Message& msg);

/**
 * Message id type.
 *
 * The message system uses message id's that are unique per sender.
 *
 * \relates Message
 */
typedef unsigned long msgid_t;

/**
 * A pair that contains a message id, and a message.
 *
 * \relates Message
 */
typedef std::pair<msgid_t, Message> msgpair_t;

/**
 * \class MessageIdLess message.h <Pieces/Message>
 * \brief Compares message ids.
 *
 * This class is meant for internal use.
 * It is unlikely that users of Pieces will have to use this class directly.
 *
 * Comparison operator used to find a given message id in a sorted list.
 *
 * \relates Message
 */
class MessageIdLess
{
public:

    /** Returns true if \a idl is less than \a idr */
    bool operator()(const msgid_t& idl, msgid_t idr)
    {
        return (idl < idr);
    }

    /** Returns true if the id of \a msg is less than \a id */
    bool operator()(const msgpair_t& msg, msgid_t id)
    {
        return operator()(msg.first, id);
    }

    /** Returns true if \a id is less than the id of \a msg */
    bool operator()(msgid_t id, const msgpair_t& msg)
    {
        return operator()(id, msg.first);
    }

    /** Returns true if the id of \a msgl is less than the id of \a msgr */
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

} // namespace pcs

#endif // PIECES_MESSAGE_H
