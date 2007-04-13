
#ifndef PIECES_GAME_DATA_RECEIVER_THREAD_H
#define PIECES_GAME_DATA_RECEIVER_THREAD_H

#include "Pieces/global"
#include "OpenThreads/Thread"


namespace Pieces
{
class EventLoop;
class GameData;
class GameDataReceiverThreadPrivate;


/**
 * \class GameDataReceiverThread
 * \brief Background thread used by GameDataReceiver
 *
 * It's unlikely that users of pieces will ever need to use this class directly.
 *
 * \author Robin Pedersen
 */
class GameDataReceiverThread : public OpenThreads::Thread
{
public:
    GameDataReceiverThread(EventLoop* eventLoop, port_t port);
    ~GameDataReceiverThread();

    void abort();

protected:
    virtual void run();

private:
    DISABLE_COPY(GameDataReceiverThread);

    GameDataReceiverThreadPrivate* d;
};

} // namespace Pieces

#endif // PIECES_GAME_DATA_RECEIVER_THREAD_H
