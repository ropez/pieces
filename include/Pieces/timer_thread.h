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

#ifndef PIECES_TIMER_THREAD_H
#define PIECES_TIMER_THREAD_H

#include "OpenThreads/Thread"
#include "Pieces/global"


namespace pcs
{
class TimerThreadPrivate;
class ByteArray;
class EventLoop;


/**
 * \class TimerThread timer_thread.h <Pieces/TimerThread>
 * \brief A thread that posts an event after a given delay.
 *
 * This class is meant for internal use.
 * It is unlikely that users of Pieces will have to use this class directly.
 *
 * This class is used by Timer.
 *
 * The tread sleeps until the given delay has elapsed, then wakes up to post
 * an event on the event-loop passed to the contructor.
 *
 * If it is a repeating timer, it then waits until it's triggered again,
 * otherwise it terminates.
 *
 * \see Timer
 * \author Robin Pedersen
 */
class TimerThread : public OpenThreads::Thread
{
public:

    /**
     * Create a timer-thread that posts event to the given \a eventLoop.
     */
    TimerThread(EventLoop* eventLoop);

    /**
     * Destructor.
     *
     * Destructing a running timer is illegal.
     */
    ~TimerThread();

    /**
     * If the timer-thread is repeating, it will continue to run after it's
     * triggered, and get triggered again each time the delay elapses.
     */
    bool isRepeating() const;

    /**
     * Change the repeating property.
     *
     * If the timer-thread is repeating, it will continue to run after it's
     * triggered, and get triggered again each time the delay elapses.
     */
    void setRepeating(bool on);

    /**
     * Returns the timer id.
     */
    int getTimerId() const;

    /**
     * Set the timer id.
     */
    void setTimerId(int id);

    /**
     * The delay is how long it sleeps before it's triggered.
     *
     * The delay time is in milli-seconds.
     */
    unsigned long getDelay() const;

    /**
     * Set the delay time to how long it should sleep before it's triggered.
     *
     * The delay time is in milli-seconds.
     */
    void setDelay(unsigned long msec);

    /**
     * Stop the timer-thread.
     *
     * When the function returns, the timer-thread is guaranteed to have
     * stopped completely, and it's safe to delete the object.
     *
     * This function is thread-safe.
     */
    void abort();

protected:

    /**
     * Timer-thread main loop.
     *
     * Sleeps until the delay time has elapsed, or until it's aborted. If it
     * wakes up and haven't been aborted, it posts the event on the event-loop.
     * If it's repeating it then restarts, otherwise it exits.
     */
    virtual void run();


private:
    DISABLE_COPY(TimerThread);

    TimerThreadPrivate* d;
};

} // namespace pcs

#endif // PIECES_TIMER_THREAD_H
