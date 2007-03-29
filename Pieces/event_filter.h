
#ifndef PIECES_EVENT_FILTER_H
#define PIECES_EVENT_FILTER_H

#include "Pieces/EventHandler"


namespace Pieces
{


/**
 * \class EventFilter
 * \brief Base class for event filters.
 *
 * An event filter can be used to handle some event before they are sent to the
 * "real" event handler.
 *
 * This is a base class that provides no other features than to forward all
 * events to the next event handler.
 *
 * Many filters can be linked together to a \em chain of event handlers, that
 * together handles events for an event loop.
 *
 * \author Robin Pedersen
 */
class EventFilter : public EventHandler
{
public:

    /**
     * Create an event filter that by default forwards all events to the
     * \a nextHandler.
     */
    EventFilter(EventHandler* nextHandler);

protected:

    /**
     * Forwards all events.
     */
    virtual void handle(Event* event);

private:
    DISABLE_COPY(EventFilter);

    EventHandler* m_nextHandler;
};

} // namespace Pieces

#endif // PIECES_EVENT_FILTER_H