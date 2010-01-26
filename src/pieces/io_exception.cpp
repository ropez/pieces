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
#include "Pieces/IOException"


namespace pcs
{

IOException::IOException()
: Exception()
{
}


IOException::IOException(const std::string& message)
: Exception(message)
{
}


IOException::IOException(const std::string& where, const std::string& message)
: Exception(where, message)
{
}


std::string IOException::getClassName() const
{
    return "IOException";
}

} // namespace pcs
