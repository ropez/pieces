
#ifndef PIECES_GAME_DATA_SENDER_H
#define PIECES_GAME_DATA_SENDER_H

#include "Pieces/global"


namespace Pieces
{
class SocketAddress;
class FrameData;
class GameDataSenderPrivate;


/**
 * \class GameDataSender
 * \brief Sends game world data to peers.
 *
 * \author Borge Jakobsen
 */
class GameDataSender
{
public:
    GameDataSender();
    ~GameDataSender();

    framenum_t getFrameNumber() const;

    void addReceiver(const SocketAddress& socket);
    void removeReceiver(const SocketAddress& socket);

    FrameData getFrameData(framenum_t frameNum) const;

    void sendFrameData(const FrameData& frame);

private:
    DISABLE_COPY(GameDataSender);

    GameDataSenderPrivate* d;
};

} // namespace Pieces

#endif // PIECES_GAME_DATA_SENDER_H
