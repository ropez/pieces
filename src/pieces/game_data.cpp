
#include "Pieces/GameData"
#include "Pieces/InvalidKeyException"


namespace pcs
{

GameData::GameData(size_t maxFrames)
: d(new Data)
{
    d->maxFrames = maxFrames;
}


GameData::GameData(const GameData& other)
: d(other.d)
{
}


GameData& GameData::operator=(const GameData& other)
{
    d = other.d;
    return *this;
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
    map_t::iterator it = d->frameData.find(frameNum);
    if (it != d->frameData.end())
    {
        // Update
        it->second = frameData;
    }
    else
    {
        if (d->frameData.size() >= d->maxFrames)
        {
            // Remove first element
            d->frameData.erase(d->frameData.begin());
        }

        // Insert new data
        d->frameData.insert(map_t::value_type(frameNum, frameData));
    }
}


GameData::Data::Data()
: SharedData()
, maxFrames(-1)
, frameData()
{
}


GameData::Data::Data(const Data& other)
: SharedData()
, maxFrames(other.maxFrames)
, frameData(other.frameData)
{
}


GameData::Data& GameData::Data::operator=(const Data& other)
{
    maxFrames = other.maxFrames;
    frameData = other.frameData;
    return *this;
}

} // namespace pcs
