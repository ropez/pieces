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
#ifndef PIECES_DISCONNECTED_EXCEPTION_H
#define PIECES_DISCONNECTED_EXCEPTION_H

#include "Pieces/Exception"


namespace pcs
{


/**
 * \class DisconnectedException disconnected_exception.h <Pieces/DisconnectedException>
 * \brief Input/output exception class.
 *
 * This type of exception is thrown when a TCPSocket is disconnected while
 * operation is performed on it.
 *
 * \author Thomas Bakken, Tord Heimdal
 */
class DisconnectedException : public Exception
{
public:

    /**
     * Default constructor.
     */
    DisconnectedException();

    /**
     * Constructor that takes a message.
     */
    DisconnectedException(const std::string& message);

    /**
     * Constructor that takes a function name and a message.
     */
    DisconnectedException(const std::string& where, const std::string& message);

    /**
     * Returns the name of the class.
     */
    virtual std::string getClassName() const;
};

} // namespace pcs

#endif // PIECES_DISCONNECTED_EXCEPTION_H
