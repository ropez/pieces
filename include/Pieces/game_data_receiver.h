
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

