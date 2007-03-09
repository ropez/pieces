
#ifndef PIECES_GAME_EVENT_H
#define PIECES_GAME_EVENT_H

#include "Pieces/Event"

namespace Pieces
{


class GameEvent : public Event
{
public:
    GameEvent();

protected:
    virtual ~GameEvent();

    virtual void dispatch(EventHandler* h);
};

} // namespace Pieces

#endif // PIECES_GAME_EVENT_H
