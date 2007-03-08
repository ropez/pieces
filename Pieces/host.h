
#ifndef PIECES_HOST_H
#define PIECES_HOST_H

#include "Pieces/EventHandler"


namespace Pieces
{
class EventLoop;


class Host : public EventHandler
{
public:
    Host();

    ~Host();

    EventLoop* eventLoop();

    void exec();

protected:
    virtual void event(const Event& event);

private:
    EventLoop* m_eventLoop;
};

} // namespace Pieces

#endif // PIECES_HOST_H
