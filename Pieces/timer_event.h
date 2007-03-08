
#ifndef PIECES_TIMER_EVENT_H
#define PIECES_TIMER_EVENT_H

#include "Pieces/Event"

namespace Pieces
{


class TimerEvent : public Event
{
public:
    TimerEvent();

protected:
    virtual ~TimerEvent();

    virtual void trigger(EventHandler* h);
};

} // namespace Pieces

#endif // PIECES_TIMER_EVENT_H
