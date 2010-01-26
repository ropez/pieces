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

#include "Pieces/EventHandler"
#include "Pieces/Event"
#include "Pieces/TimerEvent"
#include "Pieces/GameEvent"
#include "Pieces/NetworkEvent"
#include "Pieces/MessageReceivedEvent"
#include "Pieces/ConnectedEvent"
#include "Pieces/DisconnectedEvent"
#include "Pieces/InputEvent"
#include "Pieces/GameDataEvent"


namespace pcs
{

EventHandler::EventHandler()
{
}


EventHandler::~EventHandler()
{
}


void EventHandler::handle(Event*)
{
}


void EventHandler::handle(TimerEvent* event)
{
    // Fall back to default handler function
    Event* e = event;
    handle(e);
}


void EventHandler::handle(GameEvent* event)
{
    // Fall back to default handler function
    Event* e = event;
    handle(e);
}

void EventHandler::handle(NetworkEvent* event)
{
    // Fall back to default handler function
    Event* e = event;
    handle(e);
}

void EventHandler::handle(MessageReceivedEvent* event)
{
    // Fall back to default handler function
    NetworkEvent* e = event;
    handle(e);
}

void EventHandler::handle(ConnectedEvent* event)
{
    // Fall back to default handler function
    NetworkEvent* e = event;
    handle(e);
}

void EventHandler::handle(DisconnectedEvent* event)
{
    // Fall back to default handler function
    NetworkEvent* e = event;
    handle(e);
}

void EventHandler::handle(InputEvent* event)
{
    // Fall back to default handler function
    Event* e = event;
    handle(e);
}

void EventHandler::handle(GameDataEvent* event)
{
    // Fall back to default handler function
    Event* e = event;
    handle(e);
}

}
