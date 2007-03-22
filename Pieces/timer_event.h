
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

    int getTimerId() const;

protected:
    virtual ~TimerEvent();

    virtual void dispatch(EventHandler* h);

private:
    int m_timerId;
};

} // namespace Pieces

#endif // PIECES_TIMER_EVENT_H
