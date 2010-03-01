/*
    Copyright 2007,2010 The Pieces Team

    This file is part of Pieces.

    Pieces is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Pieces is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
    more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Pieces.  If not, see <http://www.gnu.org/licenses/>.
*/

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

} // namespace pcs
