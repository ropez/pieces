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

#ifndef PIECES_GAME_EVENT_H
#define PIECES_GAME_EVENT_H

#include "Pieces/Event"

namespace pcs
{


/**
 * \class GameEvent game_event.h <Pieces/GameEvent>
 * \brief A game-specific event.
 *
 * \deprecated Use MessageReceivedEvent instead.
 *
 * This class is meant to be used as base class for game-specific events.
 * Game-events are created by the user host application, and propagated to the
 * peers by the pieces framework.
 *
 * Game events can have an associated event type, in addition to the generic
 * data storage provided by the basic Event.
 *
 * \author Robin Pedersen
 */
class GameEvent : public Event
{
    friend class AutoPointer<GameEvent>;

public:

    /**
     * Creates a game-event and sets the type property to the given \a type.
     */
    explicit GameEvent(int type = 0);

    /**
     * Returns a deep copy of this event.
     */
    virtual AutoPointer<Event> clone() const;

    /**
     * Calls h->handle(this).
     */
    virtual void dispatch(EventHandler* h);

    /**
     * Returns the event type.
     */
    int type() const;

    /**
     * Set or change the event type.
     */
    void setType(int type);

protected:

    /**
     * Protected destructor prevents stack allocation.
     */
    virtual ~GameEvent();

private:
    DISABLE_COPY(GameEvent);
    int m_type;
};

} // namespace pcs

#endif // PIECES_GAME_EVENT_H
