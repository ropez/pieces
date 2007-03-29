
#ifndef PIECES_PEER_H
#define PIECES_PEER_H

#include "Pieces/EventHandler"


namespace Pieces
{
class EventLoop;
class ConnectionManager;
class SocketAddress;
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

    ConnectionManager* connectionManager() const;

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

    /**
     * This is the top level event dispatcher.
     *
     * It handles all events in the event queue. Some of them are forwarded to
     * other special purpose event handlers like userDefinedEvent().
     */
    virtual void handle(Event* event);

private:
    DISABLE_COPY(Peer);

    PeerPrivate* d;
};

} // namespace Pieces

#endif // PIECES_PEER_H
