
#ifndef PIECES_TIMER_EVENT_H
#define PIECES_TIMER_EVENT_H

#include "Pieces/Event"

namespace pcs
{


class TimerEvent : public Event
{
    friend class AutoPointer<TimerEvent>;

public:
    TimerEvent(int timerId = 0);

protected:

    virtual ~TimerEvent();

public:

    virtual AutoPointer<Event> clone() const;
    virtual void dispatch(EventHandler* h);

    int getTimerId() const;

private:
    DISABLE_COPY(TimerEvent);
    int m_timerId;
};

} // namespace pcs

#endif // PIECES_TIMER_EVENT_H
