
#ifndef PIECES_GAME_DATA_SENDER_H
#define PIECES_GAME_DATA_SENDER_H

#include "Pieces/global"


namespace pcs
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

    void sendFrameData(const FrameData& frameData);

private:
    DISABLE_COPY(GameDataSender);

    GameDataSenderPrivate* d;
};

} // namespace pcs

#endif // PIECES_GAME_DATA_SENDER_H
