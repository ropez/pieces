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

#ifndef PIECES_INPUT_EVENT_H
#define PIECES_INPUT_EVENT_H

#include "Pieces/Event"

namespace pcs
{


/**
 * \class InputEvent input_event.h <Pieces/InputEvent>
 * \brief Game-specific input event.
 *
 * \deprecated Use MessageReceivedEvent instead.
 *
 * This kind of event is created by peers as result of user input, and
 * propagated to the host by the framework.
 *
 * \author Robin Pedersen
 */
class InputEvent : public Event
{
    friend class AutoPointer<InputEvent>;

public:

    /**
     * Creates an input-event and sets the type property to the given \a type.
     */
    explicit InputEvent(int type = 0);

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
    virtual ~InputEvent();

private:
    DISABLE_COPY(InputEvent);
    int m_type;
};

} // namespace pcs

#endif // PIECES_INPUT_EVENT_H
