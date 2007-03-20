
#include "Pieces/Host"

#include "Pieces/TCPConnectionManager"

#include "Pieces/NetworkEvent"
#include "Pieces/SocketAddress"
#include "Pieces/BufferStream"
#include "Pieces/IOException"
#include "Pieces/Debug"

using namespace Pieces;


class HostTest : public Host
{
protected:

    virtual void handle(NetworkEvent* event)
    {
        DEBUG << "Got network event, type " << event->type();

        try
        {
            BufferStream bf(event->data());

            std::string str;
            bf >> str;
            DEBUG << "From: " << event->getSenderAddress();
            DEBUG << "Data (as string): " << str;
        }
        catch (const IOException& e)
        {
            WARNING << e;
        }
    }

};


int main()
{
    AutoPointer<HostTest> host(new HostTest);

    host->connectionManager()->listen(2222);
    host->exec();
}
