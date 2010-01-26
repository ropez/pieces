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

#ifndef PIECES_GAME_DATA_RECEIVER_H
#define PIECES_GAME_DATA_RECEIVER_H

#include "Pieces/global"


namespace pcs
{
class EventLoop;
class FrameData;
class GameDataReceiverPrivate;


/**
 * \class GameDataReceiver game_data_receiver.h <Pieces/GameDataReceiver>
 * \brief Receives game data from a host.
 *
 * This class is meant to be used in peers.
 *
 * This class runs an internal thread that listens for incoming frame data,
 * and posts a GameDataEvent to the given EventLoop when data arrives.
 *
 * \see GameDataSender
 * \author Robin Pedersen
 */
class GameDataReceiver
{
public:

    /**
     * Create a receiver that will post events to the given \a eventLoop.
     *
     * Must call listen to start the receiver.
     */
    GameDataReceiver(EventLoop* eventLoop);

    /**
     * Stop the receiver, and release resources.
     */
    ~GameDataReceiver();

    /**
     * Start listening for game data on the given UDP port.
     */
    void listen(port_t port);

private:
    DISABLE_COPY(GameDataReceiver);

    GameDataReceiverPrivate* d;
};

} // namespace pcs

#endif // PIECES_GAME_DATA_RECEIVER_H

