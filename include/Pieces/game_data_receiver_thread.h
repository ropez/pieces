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

#ifndef PIECES_GAME_DATA_RECEIVER_THREAD_H
#define PIECES_GAME_DATA_RECEIVER_THREAD_H

#include "Pieces/global"
#include "OpenThreads/Thread"


namespace pcs
{
class EventLoop;
class GameData;
class GameDataReceiverThreadPrivate;


/**
 * \class GameDataReceiverThread game_data_receiver_thread.h <Pieces/GameDataReceiverThread>
 * \brief Background thread used by GameDataReceiver
 *
 * This class is meant for internal use.
 * It is unlikely that users of Pieces will have to use this class directly.
 *
 * The game data reveiver runs in a background thread, listening for incoming
 * UDP datagrams. When data arrives, it posts a GameDataEvent to the given
 * event loop.
 *
 * \author Robin Pedersen
 */
class GameDataReceiverThread : public OpenThreads::Thread
{
public:

    /**
     * Constructor.
     */
    GameDataReceiverThread(EventLoop* eventLoop, port_t port);

    /**
     * Destructor.
     *
     * Calls abort().
     */
    ~GameDataReceiverThread();

    /**
     * Stops the thread.
     */
    void abort();

protected:

    /**
     * Thread main loop.
     *
     * Waits for incoming datagrams, and posts a GameDataEvent when data arrives.
     */
    virtual void run();

private:
    DISABLE_COPY(GameDataReceiverThread);

    GameDataReceiverThreadPrivate* d;
};

} // namespace pcs

#endif // PIECES_GAME_DATA_RECEIVER_THREAD_H
