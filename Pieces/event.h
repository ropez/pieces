
#ifndef PIECES_EVENT_H
#define PIECES_EVENT_H

#include "Pieces/SharedData"
#include "Pieces/SharedDataPointer"
#include "Pieces/ByteArray"


namespace Pieces
{

class Event
{
public:

    /**
     * Predefined event types.
     *
     * \note Negative event types are reserved for internal use.
     */
    enum Type
    {
    };

    explicit Event(int type);
    ~Event();

    int type() const;

    void setData(const ByteArray& data);
    ByteArray data() const;

private:
    class Data : public SharedData
    {
    public:
        Data();
        Data(const Data& other);

        int type;
        ByteArray data;
    };

    SharedDataPointer<Data> d;
};

} // namespace Pieces

#endif // PIECES_EVENT_H
