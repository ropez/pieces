
#include "Pieces/GameDataEvent"


namespace Pieces
{

GameDataEvent::GameDataEvent(framenum_t frameNum)
: m_frameNum(frameNum)
{
}

framenum_t GameDataEvent::getFrameNumber() const
{
    return m_frameNum;
}

GameDataEvent::~GameDataEvent()
{
}


} // namespace Pieces
