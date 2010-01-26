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

#ifndef PIECES_ATOMIC_H
#define PIECES_ATOMIC_H

extern "C"
{

/**
 * Increments *p, and returns the truth value of the result, false if *p
 * becomes 0, true otherwise
 */
bool atomic_increment(unsigned long *p);

/**
 * Decrements *p, and returns the truth value of the result, false if *p
 * becomes 0, true otherwise
 */
bool atomic_decrement(unsigned long *p);

}

#endif // NUM_ATOMIC_H
