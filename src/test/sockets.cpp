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

                if (ch == '\n')
                {
                    // Really echo
                    ds << flush;
                }
            }
        }
        catch (const Exception& e)
        {
            ERROR << e;
            sock->close();

            // Calling close() twice
            sock.reset();
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
        TCPServer server;
        server.listen(2222);

        for (;;)
        {
            std::auto_ptr<TCPSocket> s = server.accept();

            INFO << "Accepted connection from " << s->getPeerAddress();

            // This is a memory leak!
            Session* session = new Session(s.release());
            session->start();
        }
    }
    catch (const Exception& e)
    {
        ERROR << e;
    }
}

