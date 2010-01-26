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

#include "Pieces/GameObjectDB"
#include "Pieces/GameObject"


namespace pcs
{


GameObjectDB::GameObjectDB()
: m_objects()
{
}


GameObjectDB::~GameObjectDB()
{
}


void GameObjectDB::clear()
{
    m_objects.clear();
}


GameObjectDB::ptr_t GameObjectDB::insert(objectid_t objectId, GameObject* obj)
{
    ptr_t tmp = remove(objectId);
    m_objects[objectId] = obj;
    return tmp;
}


GameObjectDB::ptr_t GameObjectDB::remove(objectid_t objectId)
{
    map_t::iterator it = m_objects.find(objectId);

    return remove(it);
}


GameObjectDB::ptr_t GameObjectDB::remove(map_t::iterator it)
{
    if (it != end())
    {
        ptr_t tmp = it->second;
        m_objects.erase(it);
        return tmp;
    }
    return 0;
}


GameObjectDB::ptr_t GameObjectDB::get(objectid_t objectId) const
{
    map_t::const_iterator it = m_objects.find(objectId);

    if (it != end())
    {
        return it->second;
    }
    return 0;
}


void GameObjectDB::updateFrameData(FrameData& frameData) const
{
    for (map_t::const_iterator it = begin(); it != end(); ++it)
    {
        const ptr_t& obj = it->second;
        obj->updateFrameData(frameData);
    }
}


void GameObjectDB::applyFrameData(framenum_t frameNum, const FrameData& frameData)
{
    for (map_t::iterator it = begin(); it != end(); ++it)
    {
        const ptr_t& obj = it->second;
        obj->applyFrameData(frameNum, frameData);
    }
}


void GameObjectDB::applyAction(int actionType, framenum_t frameNum)
{
    for (map_t::iterator it = begin(); it != end(); ++it)
    {
        const ptr_t& obj = it->second;
        obj->applyAction(actionType, frameNum);
    }
}


GameObjectDB::map_t::iterator GameObjectDB::begin()
{
    return m_objects.begin();
}


GameObjectDB::map_t::iterator GameObjectDB::end()
{
    return m_objects.end();
}


GameObjectDB::map_t::const_iterator GameObjectDB::begin() const
{
    return m_objects.begin();
}


GameObjectDB::map_t::const_iterator GameObjectDB::end() const
{
    return m_objects.end();
}

} // namespace pcs
