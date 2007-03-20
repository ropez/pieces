#include "Pieces/TCPSocket"
#include "Pieces/DataStream"
#include "Pieces/BufferStream"
#include "Pieces/InetAddress"
#include "Pieces/Exception"
#include "Pieces/Debug"

#include "OpenThreads/Thread"
#include "sys/signal.h"

using namespace Pieces;


int main()
{
    signal(SIGPIPE, SIG_IGN);
    OpenThreads::Thread::Init();

    try
    {
        TCPSocket sock;

        if (!sock.connect(InetAddress::getHostByName("localhost"), 2222))
        {
            ERROR << "Server not found";
            exit(0);
        }

        DEBUG << "Connected to " << sock.getPeerAddress();

        DataStream ds(&sock);

        int count = 10;
        while (count--)
        {
            std::stringstream str;
            str << "Bomb goes off in " << count << " seconds";
            BufferStream bs;
            bs << str.str();
            ds << 666 << bs.data() << flush;

            OpenThreads::Thread::microSleep(1000000);
        }
    }
    catch (const Exception& e)
    {
        ERROR << e;
    }
}

