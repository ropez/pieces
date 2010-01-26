/*
    Copyright 2007,2010 The Pieces Team

    This file is part of Pieces.

    Pieces is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Pieces is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
    more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Pieces.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PIECES_EVENT_HANDLER_H
#define PIECES_EVENT_HANDLER_H

#include "Pieces/global"


namespace pcs
{
class Event;
class TimerEvent;
class GameEvent;
class NetworkEvent;
class MessageReceivedEvent;
class ConnectedEvent;
class DisconnectedEvent;
class InputEvent;
class GameDataEvent;


/**
 * \class EventHandler event_handler.h <Pieces/EventHandler>
 * \brief Base class for event handlers.
 *
 * This is a base class that event-handling classes must derive from to be
 * used together with an EventLoop. This class provides absolutely no
 * functionality by itself.
 *Network
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
    friend class MessageReceivedEvent;
    friend class ConnectedEvent;
    friend class DisconnectedEvent;
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
     * Specialized event handler for network events.
     *
     * \overload
     *
     * This can be implemented to handle networks events only. The default
     * implementation forwards the events to the generic event handler.
     */
    virtual void handle(MessageReceivedEvent* event);

    /**
     * Specialized event handler for network events.
     *
     * \overload
     *
     * This can be implemented to handle networks events only. The default
     * implementation forwards the events to the generic event handler.
     */
    virtual void handle(ConnectedEvent* event);

    /**
     * Specialized event handler for network events.
     *
     * \overload
     *
     * This can be implemented to handle networks events only. The default
     * implementation forwards the events to the generic event handler.
     */
    virtual void handle(DisconnectedEvent* event);


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

} // namespace pcs

#endif // PIECES_EVENT_HANDLER_H
