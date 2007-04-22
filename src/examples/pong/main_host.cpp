#include "Pieces/Application"
#include "pong_host.h"


int main(int argc, char** argv)
{
    pcs::Application application(argc, argv);

    pcs::AutoPointer<PongHost> host(new PongHost());

    host->exec();
}
