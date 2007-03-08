
#ifndef PIECES_HOST_H
#define PIECES_HOST_H

#include "Pieces/EventHandler"


namespace Pieces
{
class TimerEvent;
class EventLoop;
class PeerInfo;


class Host : public EventHandler
{
public:
    Host();

    ~Host();

    EventLoop* eventLoop();

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
