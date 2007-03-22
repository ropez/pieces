
#ifndef PIECES_HOST_H
#define PIECES_HOST_H

#include "Pieces/EventHandler"


namespace Pieces
{
class EventLoop;
class ConnectionManager;
class TimerEvent;
class PeerInfo;
class HostPrivate;

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

    ConnectionManager* connectionManager() const;

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
    DISABLE_COPY(Host);

    HostPrivate* d;
};

} // namespace Pieces

#endif // PIECES_HOST_H
