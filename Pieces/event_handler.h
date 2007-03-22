
#ifndef PIECES_EVENT_HANDLER_H
#define PIECES_EVENT_HANDLER_H

#include "Pieces/global"


namespace Pieces
{
class Event;
class TimerEvent;
class GameEvent;
class NetworkEvent;
class InputEvent;
class GameDataEvent;


/**
 * \class EventHandler
 * \brief Base class for event handlers.
 *
 * This is a base class that event-handling classes must derive from to be
 * used together with an EventLoop. This class provides absolutely no
 * functionality by itself.
 *
 * For each incoming event, an overloaded handler() function is called with
 * a pointer to the event object.
 *
 * \see Event, EventLoop
 * \author Robin Pedersen
 */
class EventHandler
{
    friend class Event;
    friend class TimerEvent;
    friend class GameEvent;
    friend class NetworkEvent;
    friend class InputEvent;
    friend class GameDataEvent;

public:

    /**
     * Default constructor.
     */
    EventHandler();

    /**
     * Declare virtual destructor so that subclasses are properly deleted.
     */
    virtual ~EventHandler();

protected:

    /**
     * Generic event handler for all events types.
     *
     * The default implementation does nothing.
     * Implement in subclasses to handle incoming events.
     */
    virtual void handle(Event* event);


    /**
     * Specialized event handler for timer events.
     *
     * \overload
     *
     * This can be implemented to handle timer events only. The default
     * implementation forwards the events to the generic event handler.
     */
    virtual void handle(TimerEvent* event);


    /**
     * Specialized event handler for game events.
     *
     * \overload
     *
     * This can be implemented to handle game events only. The default
     * implementation forwards the events to the generic event handler.
     */
    virtual void handle(GameEvent* event);

    /**
     * Specialized event handler for network events.
     *
     * \overload
     *
     * This can be implemented to handle networks events only. The default
     * implementation forwards the events to the generic event handler.
     */
    virtual void handle(NetworkEvent* event);


    /**
     * Specialized event handler for input events.
     *
     * \overload
     *
     * This can be implemented to handle input events only. The default
     * implementation forwards the events to the generic event handler.
     */
    virtual void handle(InputEvent* event);


    /**
     * Specialized event handler for input events.
     *
     * \overload
     *
     * This can be implemented to handle input events only. The default
     * implementation forwards the events to the generic event handler.
     */
    virtual void handle(GameDataEvent* event);
};

} // namespace Pieces

#endif // PIECES_EVENT_HANDLER_H
