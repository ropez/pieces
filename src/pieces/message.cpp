
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


Message::Message(int messageType, const PropertyList& messageData)
: d(new Data)
{
    d->type = messageType;
    d->data = messageData;
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
    d->data.clear();
}


void Message::setMessageType(int messageType)
{
    d->type = messageType;
}


int Message::getMessageType() const
{
    return d->type;
}


void Message::setMessageData(const PropertyList& messageData)
{
    d->data = messageData;
}


PropertyList Message::getMessageData() const
{
    return d->data;
}


Message::Data::Data()
: SharedData()
, type(NO_MESSAGE_TYPE)
, data()
{
}


Message::Data::Data(const Data& other)
: SharedData()
, type(other.type)
, data(other.data)
{
}


Message::Data& Message::Data::operator=(const Data& other)
{
    type = other.type;
    data = other.data;

    return *this;
}


DataStream& operator<<(DataStream& ds, const Message& msg)
{
    return ds << msg.getMessageType() << msg.getMessageData();
}


DataStream& operator>>(DataStream& ds, Message& msg)
{
    msg.clear();

    int messageType = NO_MESSAGE_TYPE;
    ds >> messageType;
    msg.setMessageType(messageType);

    PropertyList messageData;
    ds >> messageData;
    msg.setMessageData(messageData);

    return ds;
}

} // namespace Pieces
