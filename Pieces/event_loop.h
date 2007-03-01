
#ifndef PIECES_EVENT_LOOP_H
#define PIECES_EVENT_LOOP_H

#include "Pieces/Event"


namespace Pieces
{
class EventQueue;


/**
 * \class EventLoop
 * \brief Basic interface for building event-loops.
 *
 * This is an abstract base class that provides derived classes with an event
 * loop. A subclass must implement event() to handle incoming event. New events
 * are queued (posted) with postEvent().
 *
 * To run the event-loop, call exec(). The thread that called exec() will be
 * used to call event() for each incoming event, and otherwise blocked.
 *
 * To exit the event loop, and return from exec(), call quit(). This will post
 * a special quit event that is not forwarded to the event handler. The quit
 * event will be at the back of the queue, so all events posted before that
 * will be processed before the loop exits.
 *
 * \author Robin Pedersen
 */
class EventLoop
{
public:

    /**
     * Create event-loop object.
     */
    EventLoop();

    /**
     * Destructor.
     *
     * Deleting a running event-loop is illegal.
     */
    virtual ~EventLoop();

    /**
     * Execute the event-loop.
     *
     * This makes the current thread enter the event-loop, and start processing
     * events. Each event posted with postEvent() results in a call to event().
     * This is done on the same thread that called exec().
     *
     * To exit from the event-loop, call quit().
     *
     * This function must only be called from one thread.
     */
    void exec();

    /**
     * Quit the event-loop.
     *
     * Posts a special quit-event. When this event is seens by the internal
     * event dispatcher it returns from the exec() call instead of passing the
     * event to the event handler.
     *
     * \note This function returns immediately.
     * \note This function is thread-safe.
     */
    void quit();

    /**
     * Post an event to the event-loop.
     *
     * The event is queued, and later processed by the event() function.
     *
     * \note This function returns immediately.
     * \note This function is thread-safe.
     */
    void postEvent(const Event& e);

protected:

    /**
     * This function is called once for each event.
     *
     * Implement in subclasses to handle incoming events.
     */
    virtual void event(const Event& e) = 0;

private:
    // Disable copy
    EventLoop(const EventLoop&);
    EventLoop& operator=(const EventLoop&);

    EventQueue* m_queue;
};

} // namespace Pieces

#endif // PIECES_EVENT_LOOP_H
