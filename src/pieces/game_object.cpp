
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
    typedef ReferencePointer<GameObjectAction> action_ptr_t;
    typedef std::map<int, action_ptr_t> action_map_t;

    action_map_t actions;
};

GameObject::GameObject(objectid_t objectId)
: Object(objectId)
, d(new GameObjectPrivate)
{
}


GameObject::~GameObject()
{
    delete d;
}


void GameObject::encode(DataStream&) const
{
}


void GameObject::decode(DataStream&)
{
}


void GameObject::updateFrameData(FrameData& frame) const
{
    // Encode object data
    BufferStream s;
    encode(s);

    ByteArray oldData;
    try
    {
        oldData = frame.getObjectData(getObjectId());
    }
    catch (const InvalidKeyException&)
    {
        oldData = ByteArray();
    }

    // Avoid replacing equal data, to maximize effect of implicit sharing
    if (oldData.isEmpty() || s.data() != oldData)
    {
        frame.setObjectData(getObjectId(), s.data());
    }
}


void GameObject::applyFrameData(const FrameData& frame)
{
    // Object data
    BufferStream s(frame.getObjectData(getObjectId()));

    // Decode object data from stream
    decode(s);
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
