#include "Pieces/Debug"
#include "Pieces/InetAddress"
#include "Pieces/SocketAddress"
#include "Pieces/TCPServer"
#include "Pieces/TCPSocket"
#include "Pieces/Exception"
#include "OpenThreads/Thread"


using namespace Pieces;

class Session : public OpenThreads::Thread
{
public:
    Session(TCPSocket* socket)
    : sock(socket)
    {
    }

protected:
    void run()
    {
        for (;;)
        {
            ByteArray ba = sock->read();

            if (ba.isEmpty())
            {
                INFO << "Disconnected";
                return;
            }

            DEBUG << ba.data();

            // Echo
            sock->write(ba);
        }
    }

private:
    std::auto_ptr<TCPSocket> sock;
};


int main()
{
    using namespace Pieces;

    // Echo server, accepting one connection at a time
    try
    {
        SocketAddress serverAddress;
        serverAddress.setPort(2222);
        TCPServer server;
        server.listen(serverAddress);

        for (;;)
        {
            std::auto_ptr<TCPSocket> s = server.accept();

            INFO << "Accepted connection";

            // This is a memory leak!
            (new Session(s.release()))->start();
        }
    }
    catch (const Exception& e)
    {
        ERROR << e;
    }
}

