
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
        NOTHING,

        USER_DEFINED = 0x1000
    };

    explicit Event(int type = NOTHING);

    int type() const;

    bool isUserDefined() const;

    void setData(const ByteArray& data);
    ByteArray data() const;

protected:
    ~Event();

private:
    friend class std::auto_ptr<Event>;

    Event(const Event&);
    Event& operator=(const Event&);

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
