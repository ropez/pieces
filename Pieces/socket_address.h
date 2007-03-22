
#ifndef PIECES_SOCKET_ADDRESS_H
#define PIECES_SOCKET_ADDRESS_H

#include "Pieces/global"
#include "Pieces/InetAddress"



namespace Pieces
{

class DataStream;



class SocketAddress
{
public:

    SocketAddress();
    ~SocketAddress();

    SocketAddress(const InetAddress& addr, port_t port);

    SocketAddress(const SocketAddress& other);
    SocketAddress& operator=(const SocketAddress& other);

    bool isNull() const;

    InetAddress getInetAddress() const;
    void setInetAddress(const InetAddress& addr);

    port_t getPort() const;
    void setPort(port_t port);

private:
    InetAddress m_address;
    port_t m_port;
};

int compare(const SocketAddress& op1, const SocketAddress& op2);

bool operator==(const SocketAddress& op1, const SocketAddress& op2);
bool operator!=(const SocketAddress& op1, const SocketAddress& op2);
bool operator<(const SocketAddress& op1, const SocketAddress& op2);
bool operator>(const SocketAddress& op1, const SocketAddress& op2);
bool operator<=(const SocketAddress& op1, const SocketAddress& op2);
bool operator>=(const SocketAddress& op1, const SocketAddress& op2);

DataStream& operator<<(DataStream& ds, const SocketAddress& sa);
DataStream& operator>>(DataStream& ds, SocketAddress& sa);

std::ostream& operator<<(std::ostream& os, const SocketAddress& sa);

} // namespace Pieces

#endif // PIECES_SOCKET_ADDRESS_H
