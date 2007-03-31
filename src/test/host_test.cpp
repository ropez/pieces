
#include "Pieces/Application"
#include "Pieces/Host"

#include "Pieces/ConnectionManager"

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
        PDEBUG << "Got network event, type " << event->type();

        try
        {
            Message message = event->getMessage();

            PDEBUG << "From: " << event->getSenderAddress();
            PDEBUG << "Message type: " << message.getMessageType();
            PDEBUG << "Data (as string): " << message.get<std::string>(PR_TEXT);
        }
        catch (const IOException& e)
        {
            PWARNING << e;
        }
    }
};


int main(int argc, char** argv)
{
    Application application(argc, argv);

    AutoPointer<HostTest> host(new HostTest);

    host->startListening(2222);
    host->exec();
}
