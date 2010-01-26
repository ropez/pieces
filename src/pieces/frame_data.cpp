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

#include "Pieces/FrameData"
#include "Pieces/DataStream"
#include "Pieces/InvalidKeyException"

#include "Pieces/Debug"

#include <sstream>

namespace pcs
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
    // Maximize effect of implicit sharing by only replacing changed data.
    // This code is written so that it should only do one lookup in the map.
    map_t::iterator it = d->objectData.lower_bound(objectId);
    if (it == d->objectData.end() || it->first != objectId)
    {
        // Not found, inserting using the position we already know

        // Unfortunately, to use map::insert efficiently, without lookup,
        // the iterator must point to the element that PRECEDES the position
        // where we want to insert, which is pretty stupid
        if (it != d->objectData.begin())
        {
            --it;
        }

        d->objectData.insert(it, pair_t(objectId, data));
    }
    else if (it->second != data)
    {
        // Found, but must be replaced
        it->second = data;
    }
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

} // namespace pcs
