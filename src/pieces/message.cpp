
#include "Pieces/Message"


namespace pcs
{

Message::Message()
: d(new Data)
{
}


Message::~Message()
{
}


Message::Message(int messageType, flags_t flags)
: d(new Data)
{
    d->type = messageType;
    d->flags = flags;
}

Message::Message(const Message& other)
: d(other.d)
{
}


Message& Message::operator=(const Message& other)
{
    d = other.d;
    return *this;
}


void Message::clear()
{
    d->type = NO_MESSAGE_TYPE;
    d->flags = 0;
    d->properties.clear();
}


void Message::setMessageType(int messageType)
{
    d->type = messageType;
}


int Message::getMessageType() const
{
    return d->type;
}


void Message::setFlags(flags_t flags)
{
    d->flags = flags;
}


flags_t Message::getFlags() const
{
    return d->flags;
}


void Message::setProperties(const PropertyList& properties)
{
    d->properties = properties;
}


PropertyList Message::getProperties() const
{
    return d->properties;
}


Message::Data::Data()
: SharedData()
, type(NO_MESSAGE_TYPE)
, flags(0)
, properties()
{
}


Message::Data::Data(const Data& other)
: SharedData()
, type(other.type)
, flags(other.flags)
, properties(other.properties)
{
}


Message::Data& Message::Data::operator=(const Data& other)
{
    type = other.type;
    flags = other.flags;
    properties = other.properties;

    return *this;
}


DataStream& operator<<(DataStream& ds, const Message& msg)
{
    return ds << msg.getMessageType() << msg.getFlags() << msg.getProperties();
}


DataStream& operator>>(DataStream& ds, Message& msg)
{
    msg.clear();

    int messageType = NO_MESSAGE_TYPE;
    ds >> messageType;
    msg.setMessageType(messageType);

    flags_t flags = 0;
    ds >> flags;
    msg.setFlags(flags);

    PropertyList properties;
    ds >> properties;
    msg.setProperties(properties);

    return ds;
}

} // namespace pcs
