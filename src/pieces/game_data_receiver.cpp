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

#include "Pieces/GameDataReceiver"
#include "Pieces/GameDataReceiverThread"
#include "Pieces/GameData"
#include "Pieces/IOException"
#include "Pieces/AutoPointer"
#include "Pieces/Debug"



namespace pcs
{

class GameDataReceiverPrivate
{
public:
    GameDataReceiverPrivate();

    AutoPointer<GameDataReceiverThread> thread;

    EventLoop* eventLoop;
};

GameDataReceiverPrivate::GameDataReceiverPrivate()
: thread(0)
, eventLoop(0)
{
}


GameDataReceiver::GameDataReceiver(EventLoop* eventLoop)
: d(new GameDataReceiverPrivate)
{
    d->eventLoop = eventLoop;
}


GameDataReceiver::~GameDataReceiver()
{
    delete d;
}


void GameDataReceiver::listen(port_t port)
{
    d->thread = new GameDataReceiverThread(d->eventLoop, port);
    d->thread->start();
}

} //namespace pcs
