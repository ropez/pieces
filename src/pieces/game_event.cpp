
#include "Pieces/GameEvent"
#include "Pieces/EventHandler"


namespace pcs
{

GameEvent::GameEvent(int type)
: Event()
, m_type(type)
{
}


AutoPointer<Event> GameEvent::clone() const
{
    AutoPointer<GameEvent> event(new GameEvent(type()));

    return AutoPointer<Event>(event);
}


void GameEvent::dispatch(EventHandler* h)
{
    h->handle(this);
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

} // namespace pcs
