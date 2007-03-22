
#include "Pieces/GameDataEvent"
#include "Pieces/EventHandler"


namespace Pieces
{

GameDataEvent::GameDataEvent(framenum_t frameNum)
: m_frameNum(frameNum)
{
}


AutoPointer<Event> GameDataEvent::clone() const
{
    return AutoPointer<Event>(new GameDataEvent(getFrameNumber()));
}


void GameDataEvent::dispatch(EventHandler* h)
{
    h->handle(this);
}


framenum_t GameDataEvent::getFrameNumber() const
{
    return m_frameNum;
}



GameDataEvent::~GameDataEvent()
{
}



} // namespace Pieces
