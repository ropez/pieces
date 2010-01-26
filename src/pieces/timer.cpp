/*
    Copyright 2007,2010 The Pieces Team

    This file is part of Pieces.

    Pieces is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Pieces is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
    more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Pieces.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Pieces/Timer"
#include "Pieces/TimerThread"
#include "Pieces/ByteArray"


namespace pcs
{

class TimerPrivate
{
public:
    TimerPrivate();

    int id;

    TimerThread* thread;
    bool started;
};


TimerPrivate::TimerPrivate()
: id(0)
, thread(0)
, started(false)
{
}


Timer::Timer(EventLoop* eventLoop)
: d(new TimerPrivate)
{
    d->thread = new TimerThread(eventLoop);
}


Timer::Timer(int id, EventLoop* eventLoop)
: d(new TimerPrivate)
{
    d->id = id;
    d->thread = new TimerThread(eventLoop);
}


Timer::~Timer()
{
    // If the timer is running, stop it.
    stop();

    delete d->thread;
    delete d;
}


bool Timer::isRepeating() const
{
    return d->thread->isRepeating();
}


void Timer::setRepeating(bool on)
{
    if (!d->started)
    {
        d->thread->setRepeating(on);
    }
}


void Timer::start(unsigned long delay)
{
    stop();

    d->thread->setTimerId(d->id);
    d->thread->setDelay(delay);
    d->thread->start();
    d->started = true;
}


void Timer::stop()
{
    if (d->started)
    {
        d->thread->abort();
        d->started = false;
    }
}

} // namespace pcs
