
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
