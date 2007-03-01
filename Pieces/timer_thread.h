
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
 * The tread sleeps until the given delay has elapsed, then wakes up to post
 * an event on the event-loop passed to the contructor.
 * 
 * If it is a repeating timer, it then waits until it's triggered again, 
 * otherwise it terminates.
 * 
 * \see Timer
 * \author Robin Pedersen
 */
class TimerThread : public OpenThreads::Thread
{
public:
    
    /**
     * Create a timer-thread that posts event to the given \a eventLoop.
     */
    TimerThread(EventLoop* eventLoop);
    
    /**
     * Destructor.
     * 
     * Destructing a running timer is illegal.
     */
    ~TimerThread();
    
    /**
     * If the timer-thread is repeating, it will continue to run after it's 
     * triggered, and get triggered again each time the delay elapses.
     */
    bool isRepeating() const;
    
    /**
     * Change the repeating property.
     * 
     * If the timer-thread is repeating, it will continue to run after it's 
     * triggered, and get triggered again each time the delay elapses.
     */
    void setRepeating(bool on);
    
    /**
     * The delay is how long it sleeps before it's triggered.
     * 
     * The delay time is in milli-seconds.
     */
    unsigned long int getDelay() const;

    /**
     * Set the delay time to how long it should sleep before it's triggered.
     * 
     * The delay time is in milli-seconds.
     */
    void setDelay(unsigned long int ms);
    
    /**
     * The event that is posted when the timer is triggered.
     */
    Event getEvent() const;
    
    /**
     * Set the event to post when the timer is triggered.
     */
    void setEvent(const Event& event);
    
    /**
     * Stop the timer-thread.
     * 
     * When the function returns, the timer-thread is guaranteed to have 
     * stopped completely, and it's safe to delete the object.
     * 
     * This function is thread-safe.
     */
    void abort();
    
protected:
    
    /**
     * Timer-thread main loop.
     * 
     * Sleeps until the delay time has elapsed, or until it's aborted. If it 
     * wakes up and haven't been aborted, it posts the event on the event-loop.
     * If it's repeating it then restarts, otherwise it exits.
     */
    virtual void run();
    
    
private:
    
    // Disabled copy
    TimerThread(const TimerThread&);
    TimerThread& operator=(const TimerThread&);
    
    TimerThreadPrivate* d;
};

} // namespace Pieces

#endif // PIECES_TIMER_THREAD_H
