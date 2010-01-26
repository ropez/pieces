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
