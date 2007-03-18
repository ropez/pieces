
#include "Pieces/FrameData"


namespace Pieces
{

FrameData::FrameData()
: d(new Data)
{
}


bool FrameData::hasObjectData(objectid_t objectId) const
{
    map_t::const_iterator it = d->objectData.find(objectId);

    return (it != d->objectData.end());
}


ByteArray FrameData::getObjectData(objectid_t objectId) const
{
    map_t::const_iterator it = d->objectData.find(objectId);

    if (it == d->objectData.end())
        return ByteArray();

    return it->second;
}


bool FrameData::removeObjectData(objectid_t objectId)
{
    map_t::iterator it = d->objectData.find(objectId);

    if (it == d->objectData.end())
        return false;

    d->objectData.erase(it);
    return true;
}


void FrameData::setObjectData(objectid_t objectId, const ByteArray& data)
{
    d->objectData[objectId] = data;
}


FrameData::Data::Data()
: SharedData()
, objectData()
{
}


FrameData::Data::Data(const Data& other)
: SharedData()
, objectData(other.objectData)
{
}


FrameData::Data& FrameData::Data::operator=(const Data& other)
{
    objectData = other.objectData;
    return *this;
}

} // namespace Pieces
