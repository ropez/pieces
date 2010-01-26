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

#include "Pieces/Application"
#include "OpenThreads/Thread"

#if defined WIN32
#include <winsock2.h>
#endif


namespace pcs
{

class ApplicationPrivate
{
public:
    int argc;
    char** argv;
};


Application::Application(int argc, char** argv)
: d(new ApplicationPrivate)
{
    // TODO: Check that app == 0

    d->argc = argc;
    d->argv = argv;

#if defined WIN32
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD( 2, 2 );

    err = WSAStartup( wVersionRequested, &wsaData );
#endif

    OpenThreads::Thread::Init();

    app = this;
}


Application::~Application()
{
    app = 0;

#if defined WIN32
    WSACleanup();
#endif

    delete d;
}


int Application::argc() const
{
    return d->argc;
}


std::string Application::arg(int index) const
{
    return d->argv[index];
}


Application* app = 0;

} // namespace pcs
