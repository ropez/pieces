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

#include "Pieces/GameObject"
#include "Pieces/GameObjectAction"
#include "Pieces/BufferStream"
#include "Pieces/FrameData"
#include "Pieces/InvalidKeyException"
#include "Pieces/ReferencePointer"

#include <map>


namespace pcs
{

class GameObjectPrivate
{
public:
    GameObjectPrivate();

    typedef ReferencePointer<GameObjectAction> action_ptr_t;
    typedef std::map<int, action_ptr_t> action_map_t;

    framenum_t frameNum;
    action_map_t actions;
};


GameObjectPrivate::GameObjectPrivate()
: frameNum(0)
, actions()
{
}


GameObject::GameObject(objectid_t objectId)
: Object(objectId)
, d(new GameObjectPrivate)
{
}


GameObject::~GameObject()
{
    delete d;
}


framenum_t GameObject::getFrameNumber() const
{
    return d->frameNum;
}


void GameObject::encode(DataStream&) const
{
}


void GameObject::decode(DataStream&)
{
}


void GameObject::updateFrameData(FrameData& frameData) const
{
    // Encode object data
    BufferStream s;
    encode(s);

    // Add to frame data
    frameData.setObjectData(getObjectId(), s.data());
}


void GameObject::applyFrameData(framenum_t frameNum, const FrameData& frameData)
{
    try
    {
        // Object data
        BufferStream s(frameData.getObjectData(getObjectId()));

        // Decode object data from stream
        decode(s);

        d->frameNum = frameNum;
    }
    catch (const InvalidKeyException&)
    {
        // Ignore
    }
}


void GameObject::setAction(int actionType, GameObjectAction* action)
{
    d->actions[actionType] = action;
}


void GameObject::applyAction(int actionType, framenum_t frameNum)
{
    GameObjectPrivate::action_map_t::iterator it = d->actions.find(actionType);

    if (it == d->actions.end())
        throw InvalidKeyException();

    if (it->second.isValid())
    {
        GameObjectAction* function = it->second.get();

        // Call action
        (*function)(frameNum);
    }
}

} // namespace pcs
