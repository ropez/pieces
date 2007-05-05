
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
 * This class is meant to be used in hosts.
 *
 * This class has a set of reveivers that it sends frame data to.
 *
 * \todo This class shold be made \em thread-safe.
 * \todo This should be done in a background thread, but currently blocks until all data is sent.
 * \todo Data should be sent in multiple datagrams, if it exceeds the minimum datagram size.
 * \todo This should be using multicast, but currently sends the data individually to all receivers.
 *
 * \see GameDataReceiver
 * \author Borge Jakobsen
 */
class GameDataSender
{
public:

    /**
     * Default constructor.
     *
     * Creates a socket to send data.
     */
    GameDataSender();

    /**
     * Destructor.
     *
     * Releases all resources.
     */
    ~GameDataSender();

    /**
     * Returns the current frame number.
     *
     * This is increased by one for each call to sendFrameData().
     */
    framenum_t getFrameNumber() const;

    /**
     * Adds \a socket to the set of receivers.
     */
    void addReceiver(const SocketAddress& socket);

    /**
     * Removes \a socket from the set of receivers.
     */
    void removeReceiver(const SocketAddress& socket);

    /**
     * Sends the given frame data to all receivers, and increases the
     * frame number by one.
     */
    void sendFrameData(const FrameData& frameData);

private:
    DISABLE_COPY(GameDataSender);

    GameDataSenderPrivate* d;
};

} // namespace pcs

#endif // PIECES_GAME_DATA_SENDER_H
