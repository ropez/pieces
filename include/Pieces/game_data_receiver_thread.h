
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
 * \internal
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
