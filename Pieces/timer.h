
#ifndef PIECES_TIMER_H
#define PIECES_TIMER_H

namespace Pieces
{
class TimerPrivate;
class Event;
class EventLoop;


/**
 * \class Timer
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
     * Waits for \a delay milli-seconds, then it posts the \a event on the
     * event-loop that was set with the constructor.
     *
     * Ownership of the event is transfered to the timer.
     *
     * This function returns immediately.
     */
    void start(unsigned long int delay, Event* event);

    /**
     * Stop the timer if it's running.
     *
     * It's safe to call this function even if it's not running.
     */
    void stop();

private:

    // Disabled copy
    Timer(const Timer&);
    Timer& operator=(const Timer&);

    TimerPrivate* d;
};

} // namespace Pieces

#endif // PIECES_TIMER_H
