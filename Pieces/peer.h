
#ifndef PIECES_PEER_H
#define PIECES_PEER_H

#include "Pieces/EventHandler"


namespace Pieces
{
class EventLoop;
class SocketAddress;


class Peer : public EventHandler
{
public:
    Peer();

    ~Peer();

    EventLoop* eventLoop();

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

    /**
     * Connects the peer to the given host.
     *
     * TODO: Should this be synchronous or asynchronous?
     */
    void connectToHost(const SocketAddress& hostAddress);

protected:

    /**
     * This is the top level event dispatcher.
     *
     * It handles all events in the event queue. Some of them are forwarded to
     * other special purpose event handlers like userDefinedEvent().
     */
    virtual void event(Event* event);

    /**
     * Implement this to handle user defined events.
     */
    virtual void userDefinedEvent(Event* event) = 0;

private:
    EventLoop* m_eventLoop;
};

} // namespace Pieces

#endif // PIECES_PEER_H
