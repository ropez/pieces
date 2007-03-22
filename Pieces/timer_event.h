
#ifndef PIECES_TIMER_EVENT_H
#define PIECES_TIMER_EVENT_H

#include "Pieces/Event"

namespace Pieces
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
    int m_timerId;
};

} // namespace Pieces

#endif // PIECES_TIMER_EVENT_H
