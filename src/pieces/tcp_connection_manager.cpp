
#include "Pieces/TCPConnectionManager"


namespace Pieces
{

class TCPConnectionManagerPrivate
{
public:
    TCPConnectionManagerPrivate();
};


TCPConnectionManagerPrivate::TCPConnectionManagerPrivate()
{
}


TCPConnectionManager::TCPConnectionManager()
    : d(new TCPConnectionManagerPrivate)
{
}


TCPConnectionManager::~TCPConnectionManager()
{
    delete d;
}

} // namespace Pieces
