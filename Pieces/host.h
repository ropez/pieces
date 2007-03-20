
#ifndef PIECES_HOST_H
#define PIECES_HOST_H

#include "Pieces/EventHandler"


namespace Pieces
{
class EventLoop;
class TCPConnectionManager;
class TimerEvent;
class PeerInfo;

/**
 * \class Host
 * \brief Base class for host application.
 *
 * \author Robin Pedersen
 */
class Host : public EventHandler
{
public:
    Host();

    ~Host();

    EventLoop* eventLoop() const;

    TCPConnectionManager* connectionManager() const;

    /**
     * Post an event to the event-loop.
     *
     * This is a shortcut for getEventLoop()->postEvent(e).
     *
     * \see EventLoop::postEvent()
     */
    void postEvent(Event* e);

    void exec();

    void quit();

    bool isAcceptingConnections() const;
    void setAcceptingConnections(bool v);

protected:
    virtual void handle(Event* event);

    virtual void peerConnected(PeerInfo* info);

    virtual void peerDisconnected(PeerInfo* info);

private:

    EventLoop* m_eventLoop;
    TCPConnectionManager* m_connectionManager;

    bool m_accepting;
};

} // namespace Pieces

#endif // PIECES_HOST_H
