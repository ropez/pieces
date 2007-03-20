
#ifndef PIECES_TCP_CONNECTION_H
#define PIECES_TCP_CONNECTION_H


namespace Pieces
{
class TCPConnectionPrivate;


class TCPConnection
{
public:
    TCPConnection();
    ~TCPConnection();

private:
    // Disable copy operations
    TCPConnection(const TCPConnection&);
    TCPConnection& operator=(const TCPConnection&);

    TCPConnectionPrivate* d;
};

} // namespace Pieces

#endif // PIECES_TCP_CONNECTION_H
