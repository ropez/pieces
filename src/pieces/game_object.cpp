
#include "Pieces/GameObject"
#include "Pieces/BufferStream"
#include "Pieces/FrameData"


namespace Pieces
{

GameObject::GameObject(objectid_t objectId)
: Object(objectId)
{
}


GameObject::~GameObject()
{
}


void GameObject::encode(DataStream&) const
{
}


void GameObject::decode(DataStream&)
{
}


void GameObject::update(FrameData& frame) const
{
    // Encode object data
    BufferStream s;
    encode(s);

    // Avoid replacing equal data, to maximize effect of implicit sharing
    if (frame.getObjectData(getObjectId()) != s.data())
    {
        frame.setObjectData(getObjectId(), s.data());
    }
}


void GameObject::apply(const FrameData& frame)
{
    // Object data
    BufferStream s(frame.getObjectData(getObjectId()));

    // Decode object data from stream
    decode(s);
}

} // namespace Pieces
