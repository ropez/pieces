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


int atomic_increment(unsigned long *p)
{
    int retval;
    __asm
    {
        mov             eax, p
        lock inc        [eax]
        mov             eax, 0
        setnz           al

        mov             retval, eax
    }
    return retval;
}

int atomic_decrement(unsigned long *p)
{
    int retval;
    
    __asm
    {
        mov             eax, p
        lock dec        [eax]
        mov             eax, 0
        setnz           al

        mov             retval, eax
    }

    return retval;
}

