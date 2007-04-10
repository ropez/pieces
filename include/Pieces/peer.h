
#ifndef PIECES_PEER_H
#define PIECES_PEER_H

#include "Pieces/EventHandler"


namespace Pieces
{
class EventLoop;
class ConnectionManager;
class GameDataReceiver;
class SocketAddress;
class Message;
class PeerPrivate;


/**
 * \class Peer
 * \brief Base class for peer application.
 *
 * \author Robin Pedersen
 */
class Peer : public EventHandler
{
public:
    Peer();

    ~Peer();

    EventLoop* eventLoop();

    /**
     * Connects the peer to the given host.
     *
     * Same as connectionManager()->connectTo(address).
     */
    void connectTo(const SocketAddress& address);

    /**
     * Post an event to the event-loop.
     *
     * This is a shortcut for eventLoop()->postEvent(e).
     *
     * \see EventLoop::postEvent()
     */
    void postEvent(Event* e);

    /**
     * Send a message to the host.
     *
     * The message is added to a message history list, and resent when a new
     * connection is established, in case the message is sent before a
     * connection is established to a host.
     *
     * This is a shortcut for
     * \link
     * ConnectionManager::sendMessage(const Message&)
     * connectionManager()->sendMessage(message)
     * \endlink
     */
    void sendMessage(const Message& message);

    /**
     * Enter the peer's main event loop.
     *
     * Call this function after connection to a host. The calling thread will
     * enter a loop where it handles events and sleeps while waiting for new ones.
     */
    void exec();

    /**
     * Quit the event loop.
     *
     * This will make exec() return after all event has been handled.
     */
    void quit();

protected:

    ConnectionManager* connectionManager() const;

    GameDataReceiver* receiver();

private:
    DISABLE_COPY(Peer);

    PeerPrivate* d;
};

} // namespace Pieces

#endif // PIECES_PEER_H
