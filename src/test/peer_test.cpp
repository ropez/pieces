
#include "Pieces/Peer"

#include "Pieces/TCPConnectionManager"

#include "Pieces/InetAddress"
#include "Pieces/SocketAddress"
#include "Pieces/AutoPointer"

#include <cstdlib>
#include <string>

using namespace Pieces;


class PeerTest : public Peer
{
};


int main(int argc, char** argv)
{
    AutoPointer<PeerTest> peer(new PeerTest);

    std::string hostname = "localhost";
    if (argc > 1)
    {
        hostname = argv[1];
    }

    port_t port = 2222;
    if (argc > 2)
    {
        port = std::atoi(argv[2]);
    }

    SocketAddress address(InetAddress::getHostByName(hostname), port);
    peer->connectionManager()->connectTo(address);

    peer->exec();
}
