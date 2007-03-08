
#ifndef PIECES_EVENT_H
#define PIECES_EVENT_H

#include "Pieces/SharedData"
#include "Pieces/SharedDataPointer"
#include "Pieces/ByteArray"


namespace Pieces
{
class EventHandler;


class Event
{
    friend class EventLoop;
    friend class std::auto_ptr<Event>;

public:

    /**
     * Predefined event types.
     *
     * \note Negative event types are reserved for internal use.
     */
    enum Type
    {
        NOTHING,
        TIMER_EVENT,

        USER_DEFINED = 0x1000
    };

    explicit Event(int type = NOTHING);

    int type() const;

    bool isUserDefined() const;

    void setData(const ByteArray& data);
    ByteArray data() const;

protected:
    virtual ~Event();

    virtual void trigger(EventHandler* h);

private:

    Event(const Event&);
    Event& operator=(const Event&);

    int m_type;
    ByteArray m_data;
};

} // namespace Pieces

#endif // PIECES_EVENT_H
