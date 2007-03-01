
#ifndef PIECES_EVENT_QUEUE_H
#define PIECES_EVENT_QUEUE_H

#include "Pieces/Event"


namespace Pieces
{

class EventQueuePrivate;


/**
 * Thread-safe event queue.
 */
class EventQueue
{
public:
    EventQueue();
    ~EventQueue();

    void push(const Event& e);
    Event pop();

private:
    // Disable copy
    EventQueue(const EventQueue&);
    EventQueue& operator=(const EventQueue&);

    EventQueuePrivate* d;
};

} // namespace Pieces

#endif // PIECES_EVENT_QUEUE_H
