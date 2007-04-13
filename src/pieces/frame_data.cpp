
#include "Pieces/FrameData"
#include "Pieces/DataStream"
#include "Pieces/InvalidKeyException"

#include <sstream>

namespace Pieces
{

FrameData::FrameData()
: d(new Data)
{
}


size_t FrameData::size() const
{
    return d->objectData.size();
}


bool FrameData::isEmpty() const
{
    return d->objectData.empty();
}


FrameData::map_t::const_iterator FrameData::begin() const
{
    return d->objectData.begin();
}


FrameData::map_t::const_iterator FrameData::end() const
{
    return d->objectData.end();
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
    {
        std::stringstream ss;
        ss << "Object not found, id = " << objectId;
        throw InvalidKeyException("FrameData::getObjectData", ss.str());
    }

    return it->second;
}


void FrameData::clear()
{
    d->objectData.clear();
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


DataStream& operator<<(DataStream& ds, const FrameData& fd)
{
    ds << fd.size();
    for (FrameData::map_t::const_iterator it = fd.begin(); it != fd.end(); ++it)
    {
        ds << it->first;
        ds << it->second;
    }
    return ds;
}


DataStream& operator>>(DataStream& ds, FrameData& fd)
{
    fd.clear();

    size_t size;
    ds >> size;

    for (size_t i = 0; i < size; ++i)
    {
        objectid_t id;
        ds >> id;
        ByteArray data;
        ds >> data;

        fd.setObjectData(id, data);
    }
    return ds;
}

} // namespace Pieces
