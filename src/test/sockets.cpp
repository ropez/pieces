#include "Pieces/Debug"
#include "Pieces/InetAddress"
#include "Pieces/SocketAddress"
#include "Pieces/TCPServer"
#include "Pieces/TCPSocket"
#include "Pieces/Exception"
#include "Pieces/DataStream"
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
        try
        {
            sock->setReadTimeout(50000);
            INFO << "Timeout: " << sock->getReadTimeout();

            DataStream ds(sock.get());
            for (;;)
            {
                char ch;
                ds >> ch;

                // Echo
                ds << ch;
            }
        }
        catch (const Exception& e)
        {
            ERROR << e;
            sock->close();
        }
    }

private:
    std::auto_ptr<TCPSocket> sock;
};


int main()
{
    using namespace Pieces;

    // Echo server
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

