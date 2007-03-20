
#include "Pieces/TCPConnection"


namespace Pieces
{

class TCPConnectionPrivate
{
public:
    TCPConnectionPrivate();
};


TCPConnectionPrivate::TCPConnectionPrivate()
{
}


TCPConnection::TCPConnection()
: d(new TCPConnectionPrivate)
{
}


TCPConnection::~TCPConnection()
{
    delete d;
}

} // namespace Pieces
