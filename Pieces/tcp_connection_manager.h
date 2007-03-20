
#ifndef PIECES_TCP_CONNECTION_MANAGER_H
#define PIECES_TCP_CONNECTION_MANAGER_H


namespace Pieces
{
class TCPConnectionManagerPrivate;


class TCPConnectionManager
{
public:
    TCPConnectionManager();
    ~TCPConnectionManager();

private:
    // Disable copy operations
    TCPConnectionManager(const TCPConnectionManager&);
    TCPConnectionManager& operator=(const TCPConnectionManager&);

    TCPConnectionManagerPrivate* d;
};

} // namespace Pieces

#endif // PIECES_TCP_CONNECTION_MANAGER_H
