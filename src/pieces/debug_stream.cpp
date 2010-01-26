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

#include "Pieces/DebugStream"
#include "OpenThreads/Thread"

#include <sstream>
#include <iostream>
#include <iomanip>


namespace pcs
{

OpenThreads::Mutex DebugStream::mutex;


DebugStream::DebugStream()
: std::stringstream()
{
}


DebugStream::~DebugStream()
{
    mutex.lock();
    std::cout << str() << std::endl;
    mutex.unlock();
}


std::ostream& tid(std::ostream& os)
{
    OpenThreads::Thread* thread = OpenThreads::Thread::CurrentThread();
    int threadId = (thread != 0) ? thread->getThreadId() : 0;

    return os << "[T:" << threadId << "]" << align(7);
}


std::ostream& debug(std::ostream& os)
{
    return os << tid << "DEBUG" << align(16);
}


std::ostream& info(std::ostream& os)
{
    return os << tid << "INFO" << align(16);
}


std::ostream& warning(std::ostream& os)
{
    return os << tid << "WARNING" << align(16);
}


std::ostream& error(std::ostream& os)
{
    return os << tid << "ERROR" << align(16);
}

} // namespace pcs
