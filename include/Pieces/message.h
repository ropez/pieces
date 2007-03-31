
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

} // namespace Pieces

#endif // PIECES_MESSAGE_H
