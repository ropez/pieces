
#ifndef PIECES_TIMER_THREAD_H
#define PIECES_TIMER_THREAD_H

#include "OpenThreads/Thread"


namespace Pieces
{
class TimerThreadPrivate;
class Event;
class EventLoop;


/**
 * \class TimerThread
 * \brief A thread that posts an event after a given delay.
 * 
 * This class is used internally by Timer. It's unlikely that users will need
 * to use this class directly.
 * 
 * \see Timer
 * \author Robin Pedersen
 */
class TimerThread : public OpenThreads::Thread
{
public:
    TimerThread(EventLoop* eventLoop);
    
    ~TimerThread();
    
    unsigned long int getDelay() const;

    /**
     * In milliseconds.
     */
    void setDelay(unsigned long int ms);
    
    Event getEvent() const;
    
    void setEvent(const Event& event);
    
    void abort();
    
protected:
    virtual void run();
    
    
private:
    
    // Disabled copy
    TimerThread(const TimerThread&);
    TimerThread& operator=(const TimerThread&);
    
    TimerThreadPrivate* d;
};

} // namespace Pieces

#endif // PIECES_TIMER_THREAD_H
