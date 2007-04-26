#include "Pieces/Application"
#include "Pieces/Debug"
#include "Pieces/InetAddress"
#include "Pieces/SocketAddress"
#include "Pieces/TCPServer"
#include "Pieces/TCPSocket"
#include "Pieces/Exception"
#include "Pieces/DataStream"
#include "OpenThreads/Thread"


using namespace pcs;

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
            PINFO << "Timeout: " << sock->getReadTimeout();

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
            PERROR << e;
            sock->close();

            // Calling close() twice
            sock = 0;
        }
    }

private:
    AutoPointer<TCPSocket> sock;
};


using namespace pcs;

int main(int argc, char** argv)
{
    Application application(argc, argv);

    // Echo server
    try
    {
        TCPServer server;
        server.listen(2222);

        for (;;)
        {
            AutoPointer<TCPSocket> s = server.accept();

            PINFO << "Accepted connection from " << s->getPeerAddress();

            // This is a memory leak!
            Session* session = new Session(s.release());
            session->start();
        }
    }
    catch (const Exception& e)
    {
        PERROR << e;
    }
}

