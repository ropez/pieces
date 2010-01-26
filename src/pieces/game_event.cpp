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

#include "Pieces/GameEvent"
#include "Pieces/EventHandler"


namespace pcs
{

GameEvent::GameEvent(int type)
: Event()
, m_type(type)
{
}


AutoPointer<Event> GameEvent::clone() const
{
    AutoPointer<GameEvent> event(new GameEvent(type()));

    return AutoPointer<Event>(event);
}


void GameEvent::dispatch(EventHandler* h)
{
    h->handle(this);
}


int GameEvent::type() const
{
    return m_type;
}


void GameEvent::setType(int type)
{
    m_type = type;
}


GameEvent::~GameEvent()
{
}

} // namespace pcs
