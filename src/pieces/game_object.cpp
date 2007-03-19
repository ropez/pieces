
#include "Pieces/GameObject"


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

} // namespace Pieces
