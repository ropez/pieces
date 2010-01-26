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

#ifndef PIECES_INVALID_KEY_EXCEPTION_H
#define PIECES_INVALID_KEY_EXCEPTION_H

#include "Pieces/Exception"


namespace pcs
{


/**
 * \class InvalidKeyException invalid_key_exception.h <Pieces/InvalidKeyException>
 * \brief Exceptionfor invalid key.
 *
 * This exception is thrown when a function is called with a key argument,
 * and a value for that key is not found in a data structure that stores
 * values by key.
 *
 * \author Robin Pedersen
 */
class InvalidKeyException : public Exception
{
public:

    /**
     * Default constructor.
     */
    InvalidKeyException();

    /**
     * Constructor that takes a message.
     */
    InvalidKeyException(const std::string& message);

    /**
     * Constructor that takes a function name and a message.
     */
    InvalidKeyException(const std::string& where, const std::string& message);

    /**
     * Returns the name of the class.
     */
    virtual std::string getClassName() const;
};

} // namespace pcs

#endif // PIECES_INVALID_KEY_EXCEPTION_H
