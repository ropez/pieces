
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
