
#include "Pieces/GameDataEvent"
#include "Pieces/EventHandler"


namespace Pieces
{

GameDataEvent::GameDataEvent(framenum_t frameNum, const FrameData& frameData)
: m_frameNum(frameNum)
, m_frameData(frameData)
{
}


AutoPointer<Event> GameDataEvent::clone() const
{
    return AutoPointer<Event>(new GameDataEvent(getFrameNumber(), getFrameData()));
}


void GameDataEvent::dispatch(EventHandler* h)
{
    h->handle(this);
}


framenum_t GameDataEvent::getFrameNumber() const
{
    return m_frameNum;
}


FrameData GameDataEvent::getFrameData() const
{
    return m_frameData;
}


GameDataEvent::~GameDataEvent()
{
}



} // namespace Pieces
