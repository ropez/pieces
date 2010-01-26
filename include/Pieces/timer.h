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

#ifndef PIECES_TIMER_H
#define PIECES_TIMER_H

#include "Pieces/global"

namespace pcs
{
class TimerPrivate;
class ByteArray;
class EventLoop;


/**
 * \class Timer timer.h <Pieces/Timer>
 * \brief Triggers an event on an event-loop after a given delay.
 *
 * A timer can be used to trigger an event on an event-loop after a given
 * delay. It can either be a single-shot timer that exits after posting the
 * event once, or it can repeat this until it's stopped or deleted.
 *
 * It's implemented by creating a light-weight sleeping background thread,
 * that wakes up to post the event when the delay time has elapsed.
 *
 * \author Robin Pedersen
 */
class Timer
{
public:

    /**
     * Create a timer that posts event to the given \a eventLoop.
     */
    Timer(EventLoop* eventLoop);

    /**
     * Create a timer that posts event to the given \a eventLoop.
     */
    Timer(int id, EventLoop* eventLoop);

    /**
     * Destructor.
     *
     * Stops the timer if it's running, and frees resources.
     */
    ~Timer();

    /**
     * If the timer is repeating, it will continue to run after it's
     * triggered, and get triggered again each time the delay elapses.
     */
    bool isRepeating() const;

    /**
     * Change the repeating property.
     *
     * If the timer is repeating, it will continue to run after it's
     * triggered, and get triggered again each time the delay elapses.
     *
     * Calling this function after the timer was started has no effect.
     */
    void setRepeating(bool on);

    /**
     * Start the timer.
     *
     * If the timer was running before this, it's stopped.
     *
     * Waits for \a delay milli-seconds, then it posts a TimerEvent
     * on the event-loop that was set with the constructor.
     *
     * This function returns immediately.
     */
    void start(unsigned long delay);

    /**
     * Stop the timer if it's running.
     *
     * It's safe to call this function even if it's not running.
     */
    void stop();

private:
    DISABLE_COPY(Timer);

    TimerPrivate* d;
};

} // namespace pcs

#endif // PIECES_TIMER_H
