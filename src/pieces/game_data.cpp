
#include "Pieces/GameData"
#include "Pieces/InvalidKeyException"


namespace Pieces
{

GameData::GameData()
: d(new Data)
{
}


bool GameData::hasFrameData(framenum_t frameNum) const
{
    map_t::const_iterator it = d->frameData.find(frameNum);

    return (it != d->frameData.end());
}


FrameData GameData::getFrameData(framenum_t frameNum) const
{
    map_t::const_iterator it = d->frameData.find(frameNum);

    if (it == d->frameData.end())
        throw InvalidKeyException("GameData::getFrameData", "Frame not found");

    return it->second;
}


bool GameData::removeFrameData(framenum_t frameNum)
{
    map_t::iterator it = d->frameData.find(frameNum);

    if (it == d->frameData.end())
        return false;

    d->frameData.erase(it);
    return true;
}


void GameData::setFrameData(framenum_t frameNum, const FrameData& frameData)
{
    d->frameData[frameNum] = frameData;
}


GameData::Data::Data()
: SharedData()
, frameData()
{
}


GameData::Data::Data(const Data& other)
: SharedData()
, frameData(other.frameData)
{
}


GameData::Data& GameData::Data::operator=(const Data& other)
{
    frameData = other.frameData;
    return *this;
}

} // namespace Pieces
