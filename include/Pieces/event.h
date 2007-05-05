
#ifndef PIECES_EVENT_H
#define PIECES_EVENT_H

#include "Pieces/AutoPointer"
#include "Pieces/ByteArray"


namespace pcs
{
class EventHandler;


/**
 * \class Event event.h <Pieces/Event>
 * \brief Basic event type.
 *
 * This is an abstract base class used by the event system.
 *
 * \see EventQueue, EventLoop, EventHandler
 * \author Robin Pedersen
 */
class Event
{
    friend class AutoPointer<Event>;

public:

    /**
     * Default constructor.
     */
    Event();

    /**
     * Returns a deep copy of this event.
     */
    virtual AutoPointer<Event> clone() const = 0;

    /**
     * Calls h->handle(this).
     */
    virtual void dispatch(EventHandler* h) = 0;

protected:

    /**
     * Protected destructor prevents stack allocation.
     */
    virtual ~Event();

private:
    DISABLE_COPY(Event);
};

} // namespace pcs

#endif // PIECES_EVENT_H
