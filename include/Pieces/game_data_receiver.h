
#ifndef PIECES_GAME_DATA_RECEIVER_H
#define PIECES_GAME_DATA_RECEIVER_H

#include "Pieces/global"


namespace pcs
{
class EventLoop;
class FrameData;
class GameDataReceiverPrivate;


/**
 * \class GameDataReceiver
 * \brief Receives game data at a peer.
 *
 * \author Robin Pedersen
 */
class GameDataReceiver
{
public:
    GameDataReceiver(EventLoop* eventLoop);
    ~GameDataReceiver();

    void listen(port_t port);

private:
    DISABLE_COPY(GameDataReceiver);

    GameDataReceiverPrivate* d;
};

} // namespace pcs

#endif // PIECES_GAME_DATA_RECEIVER_H

