
#ifndef PIECES_OBJECT_H
#define PIECES_OBJECT_H

#include "Pieces/global"
#include "Pieces/SharedData"


namespace pcs
{


/**
 * \class Object object.h <Pieces/Object>
 * \brief Base class for all objects.
 *
 * Has an object id.
 *
 * The Object class is a common base class for all game objects, whether they
 * implement the host, peer of both interfaces.
 *
 * \author Robin Pedersen
 */
class Object : public SharedData
{
public:

    /**
     * Create an object with the given id.
     */
    Object(objectid_t objectId);

    /**
     * Destructor.
     */
    virtual ~Object();

    /**
     * Returns the object id.
     */
    objectid_t getObjectId() const;

private:
    DISABLE_COPY(Object);

    // Id stored here
    objectid_t m_objectId;
};

} // namespace pcs

#endif // PIECES_OBJECT_H
