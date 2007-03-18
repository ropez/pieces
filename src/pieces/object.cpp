
#include "Pieces/Object"


namespace Pieces
{

Object::Object(objectid_t objectId)
: m_objectId(objectId)
{
}


Object::~Object()
{
}


objectid_t Object::getObjectId() const
{
    return m_objectId;
}

} // namespace Pieces
