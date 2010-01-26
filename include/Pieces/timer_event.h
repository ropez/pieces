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

#ifndef PIECES_TIMER_EVENT_H
#define PIECES_TIMER_EVENT_H

#include "Pieces/Event"

namespace pcs
{


/**
 * \class TimerEvent timer_event.h <Pieces/TimerEvent>
 * \brief An event triggered by a Timer.
 *
 * A timer sends this event after it's timeout time has elapsed.
 * The event contains the timer id of the timer that posted it.
 *
 * It is also possible to post this kind of event manually using
 * EventLoop::postEvent(), if the user want to implement timers in a way other
 * than using pcs::Timer.
 *
 * \author Robin Pedersen
 */
class TimerEvent : public Event
{
    friend class AutoPointer<TimerEvent>;

public:

    /**
     * Create a timer event with the given timer id.
     */
    TimerEvent(int timerId = 0);

    /**
     * Returns a deep copy of this event.
     */
    virtual AutoPointer<Event> clone() const;

    /**
     * Calls h->handle(this).
     */
    virtual void dispatch(EventHandler* h);

    /**
     * Returns the timer id.
     */
    int getTimerId() const;

protected:

    /**
     * Protected destructor prevents stack allocation.
     */
    virtual ~TimerEvent();

private:
    DISABLE_COPY(TimerEvent);
    int m_timerId;
};

} // namespace pcs

#endif // PIECES_TIMER_EVENT_H
