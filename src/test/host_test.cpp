
#include "Pieces/Host"

using namespace Pieces;


class HostTest : public Host
{
};


int main()
{
    HostTest h;
    h.exec();
}
