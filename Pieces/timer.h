
#ifndef PIECES_TIMER_H
#define PIECES_TIMER_H

namespace Pieces
{
class TimerPrivate;
class Event;
class EventLoop;


/**
 * \class Timer
 * \brief Triggers an event on an event-loop after a given delay.
 * 
 * \author Robin Pedersen
 */
class Timer
{
public:
    Timer(EventLoop* eventLoop);
    
    ~Timer();
    
    void start(unsigned long int delay, const Event& event);
    
    void stop();
    
    
private:
    
    // Disabled copy
    Timer(const Timer&);
    Timer& operator=(const Timer&);
    
    TimerPrivate* d;
};

} // namespace Pieces

#endif // PIECES_TIMER_H
