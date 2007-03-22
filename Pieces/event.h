
#ifndef PIECES_EVENT_H
#define PIECES_EVENT_H

#include "Pieces/AutoPointer"
#include "Pieces/ByteArray"


namespace Pieces
{
class EventHandler;


class Event
{
    friend class AutoPointer<Event>;

public:

    Event();

    virtual AutoPointer<Event> clone() const = 0;
    virtual void dispatch(EventHandler* h) = 0;

protected:

    virtual ~Event();

private:
    DISABLE_COPY(Event);
};

} // namespace Pieces

#endif // PIECES_EVENT_H
