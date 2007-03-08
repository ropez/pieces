
#include "Pieces/GameEvent"
#include "Pieces/EventHandler"


namespace Pieces
{

GameEvent::GameEvent()
: Event()
{
}


GameEvent::~GameEvent()
{
}


void GameEvent::trigger(EventHandler* h)
{
    h->handle(this);
}

} // namespace Pieces
