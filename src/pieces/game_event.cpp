
#include "Pieces/GameEvent"
#include "Pieces/EventHandler"


namespace Pieces
{

GameEvent::GameEvent(int type)
: Event()
, m_type(type)
{
}


int GameEvent::type() const
{
    return m_type;
}


void GameEvent::setType(int type)
{
    m_type = type;
}


GameEvent::~GameEvent()
{
}


void GameEvent::dispatch(EventHandler* h)
{
    h->handle(this);
}

} // namespace Pieces
