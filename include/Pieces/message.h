
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

    Message(int messageType, const PropertyList& messageData);

    Message(const Message& other);
    Message& operator=(const Message& other);

    /**
     * Set type to 0 and clear data.
     */
    void clear();

    void setMessageType(int messageType);
    int getMessageType() const;

    void setMessageData(const PropertyList& messageData);
    PropertyList getMessageData() const;

private:
    class Data : public SharedData
    {
    public:
        Data();

        Data(const Data& other);
        Data& operator=(const Data& other);

        int type;
        PropertyList data;
    };

    SharedDataPointer<Data> d;
};

DataStream& operator<<(DataStream& ds, const Message& msg);
DataStream& operator>>(DataStream& ds, Message& msg);

} // namespace Pieces

#endif // PIECES_MESSAGE_H
