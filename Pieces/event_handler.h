
#ifndef PIECES_EVENT_HANDLER_H
#define PIECES_EVENT_HANDLER_H

#include "Pieces/Event"


namespace Pieces
{
class EventLoop;


/**
 * \class EventHandler
 * \brief Interface for event-handling classes.
 *
 * This is an abstract interface class that event-handling classes must
 * implement to be used together with an EventLoop.
 *
 * The event-loop calls the event() function for each incoming event.
 *
 * \see Event, EventLoop
 * \author Robin Pedersen
 */
class EventHandler
{
    friend class EventLoop;

public:

    /**
     * Declare virtual destructor so that subclasses are properly deleted.
     */
    virtual ~EventHandler();

protected:

    /**
     * This function is called once for each event.
     *
     * Implement in subclasses to handle incoming events.
     */
    virtual void event(const Event& event) = 0;
};

} // namespace Pieces

#endif // PIECES_EVENT_HANDLER_H
