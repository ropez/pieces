
#ifndef PIECES_PEER_H
#define PIECES_PEER_H

#include "Pieces/EventHandler"


namespace Pieces
{
class EventLoop;


class Peer : public EventHandler
{
public:
    Peer();

    ~Peer();

    EventLoop* eventLoop();

    void exec();

protected:
    virtual void event(const Event& event);

private:
    EventLoop* m_eventLoop;
};

} // namespace Pieces

#endif // PIECES_PEER_H
