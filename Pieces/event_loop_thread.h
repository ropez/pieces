
#ifndef PIECES_EVENT_LOOP_THREAD_H
#define PIECES_EVENT_LOOP_THREAD_H

#include "OpenThreads/Thread"
#include "Pieces/global"


namespace Pieces
{
class EventLoop;
class EventHandler;


/**
 * \class EventLoopThread
 * \brief A thread that runs an event loop.
 *
 * EventLoop::exec() blocks the calling thread, and the event handler
 * is called on the same thread. This is a convenience class that runs an
 * eventloop in a background thread, and calls the event handler in this
 * thread.
 *
 * \author Robin Pedersen
 */
class EventLoopThread : public OpenThreads::Thread
{
public:

    /**
     * Create an event loop thread that will send events to the given \a handler.
     */
    EventLoopThread(EventHandler* handler);

    /**
     * Quits the event loop and joins the thread.
     */
    ~EventLoopThread();

    /**
     * Returns a pointer to the internal event loop.
     *
     * Use this to post events.
     */
    EventLoop* eventLoop() const;

protected:
    virtual void run();

private:
    DISABLE_COPY(EventLoopThread);
    EventLoop* m_eventLoop;
};

} // namespace Pieces

#endif // PIECES_EVENT_LOOP_THREAD_H
