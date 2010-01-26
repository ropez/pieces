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

#include "Pieces/InputEvent"
#include "Pieces/EventHandler"


namespace pcs
{

InputEvent::InputEvent(int type)
: Event()
, m_type(type)
{
}


AutoPointer<Event> InputEvent::clone() const
{
    AutoPointer<InputEvent> event(new InputEvent(type()));

    return AutoPointer<Event>(event);
}


void InputEvent::dispatch(EventHandler* h)
{
    h->handle(this);
}


int InputEvent::type() const
{
    return m_type;
}


void InputEvent::setType(int type)
{
    m_type = type;
}


InputEvent::~InputEvent()
{
}

} // namespace pcs
