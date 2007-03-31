
#ifndef PIECES_HOST_H
#define PIECES_HOST_H

#include "Pieces/EventHandler"


namespace Pieces
{
class EventLoop;
class ConnectionManager;
class GameDataSender;
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

    GameDataSender* sender();

    /**
     * Start accepting incoming connections on the given port.
     *
     * Same as connectionManager()->startListening(port).
     */
    void startListening(port_t port);

    /**
     * Stop accepting connections.
     *
     * Same as connectionManager()->stopListening().
     */
    void stopListening();

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
