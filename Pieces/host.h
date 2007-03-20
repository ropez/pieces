
#ifndef PIECES_HOST_H
#define PIECES_HOST_H

#include "Pieces/EventHandler"


namespace Pieces
{
class TimerEvent;
class EventLoop;
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

    EventLoop* eventLoop();

    /**
     * Post an event to the event-loop.
     *
     * This is a shortcut for eventLoop()->postEvent(e).
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

    bool m_accepting;
};

} // namespace Pieces

#endif // PIECES_HOST_H
