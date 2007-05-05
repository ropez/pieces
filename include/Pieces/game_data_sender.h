
#ifndef PIECES_GAME_DATA_SENDER_H
#define PIECES_GAME_DATA_SENDER_H

#include "Pieces/global"


namespace pcs
{
class SocketAddress;
class FrameData;
class GameDataSenderPrivate;


/**
 * \class GameDataSender game_data_sender.h <Pieces/GameDataSender>
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

    /**
     * Sends the given frame data to all receivers, and increases the
     * frame number by one.
     *
     * \todo This should be done in a background thread, but currently blocks until all data is sent.
     * \todo Data should be sent in multiple datagrams, if it exceeds the minimum datagram size.
     * \todo This should be using multicast, but currently sends the data individually to all receivers.
     */
    void sendFrameData(const FrameData& frameData);

private:
    DISABLE_COPY(GameDataSender);

    GameDataSenderPrivate* d;
};

} // namespace pcs

#endif // PIECES_GAME_DATA_SENDER_H
