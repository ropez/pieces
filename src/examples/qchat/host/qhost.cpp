
#include <Pieces/Application>
#include <Pieces/AutoPointer>

#include <Pieces/Exception>
#include <Pieces/Debug>

#include "chathost.h"

using namespace Pieces;

int main(int argc, char** argv)
{
    Application application(argc, argv);

    try
    {
        AutoPointer<ChatHost> host(new ChatHost);

        host->startListening(2222);

        host->exec();
    }
    catch (const Exception& e)
    {
        PERROR << e;
    }
}

