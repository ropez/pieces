
#include "Pieces/Message"


namespace Pieces
{

Message::Message()
: d(new Data)
{
}


Message::~Message()
{
}


Message::Message(int messageType, const PropertyList& properties)
: d(new Data)
{
    d->type = messageType;
    d->properties = properties;
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
, properties()
{
}


Message::Data::Data(const Data& other)
: SharedData()
, type(other.type)
, properties(other.properties)
{
}


Message::Data& Message::Data::operator=(const Data& other)
{
    type = other.type;
    properties = other.properties;

    return *this;
}


DataStream& operator<<(DataStream& ds, const Message& msg)
{
    return ds << msg.getMessageType() << msg.getProperties();
}


DataStream& operator>>(DataStream& ds, Message& msg)
{
    msg.clear();

    int messageType = NO_MESSAGE_TYPE;
    ds >> messageType;
    msg.setMessageType(messageType);

    PropertyList properties;
    ds >> properties;
    msg.setProperties(properties);

    return ds;
}

} // namespace Pieces
