
#ifndef PIECES_OBJECT_H
#define PIECES_OBJECT_H

#include "Pieces/global"


namespace Pieces
{


/**
 * \class Object
 * \brief Base class for all objects.
 *
 * Has an object id.
 *
 * The Object class is a common base class for all game objects, whether they
 * implement the host, peer of both interfaces.
 *
 * \author Robin Pedersen
 */
class Object
{
public:
    Object(objectid_t objectId);
    virtual ~Object();

    objectid_t getObjectId() const;

private:
    // Disable copy operations
    Object(const Object&);
    Object& operator=(const Object&);

    // Id stored here
    objectid_t m_objectId;
};

} // namespace Pieces

#endif // PIECES_OBJECT_H
