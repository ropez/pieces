
#include "Pieces/Peer"

using namespace Pieces;


class PeerTest : public Peer
{
};


int main()
{
    PeerTest p;
    p.exec();
}
