
#include "Pieces/GameObject"
#include "Pieces/GameObjectAction"
#include "Pieces/BufferStream"
#include "Pieces/FrameData"
#include "Pieces/InvalidKeyException"
#include "Pieces/ReferencePointer"

#include <map>


namespace Pieces
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

} // namespace Pieces
