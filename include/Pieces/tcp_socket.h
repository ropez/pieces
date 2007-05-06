
#ifndef PIECES_TCP_SOCKET_H
#define PIECES_TCP_SOCKET_H

#include "Pieces/StreamTarget"
#include "Pieces/InetAddress"
#include "Pieces/SocketAddress"

namespace pcs
{
class TCPSocketPrivate;


/**
 * \class TCPSocket tcp_socket.h <Pieces/TCPSocket>
 * \brief OS independant TCP network socket.
 *
 * This class provides a simple OS indepenent interface for connection to TCP
 * servers, and sending and receiving data over TCP.
 *
 * \see TCPServer
 * \author Robin Pedersen, Tord Heimdal, Thomas Bakken, Joakim Simonsson, Borge Jacobsen
 */
class TCPSocket : public StreamTarget
{
    friend class TCPServer;

public:

    /**
     * Default contructor.
     *
     * Calls open().
     */
    TCPSocket();

    /**
     * Destructor (calls close()).
     */
    ~TCPSocket();

    /**
     * Opens a new socket.
     */
    void open();

    /**
     * Close the socket.
     *
     * Before the socket can be used again after it's closed, it must be
     * manually opened again.
     */
    void close();

    /**
     * Connect to the given address.
     */
    bool connect(const SocketAddress& addr);

    /**
     * Connect to the given address.
     */
    bool connect(const InetAddress& addr, port_t port);

    /**
     * Get the address to the peer connected to the socket.
     */
    SocketAddress getPeerAddress() const;

    /**
     * Read from socket.
     */
    ByteArray read(size_t maxSize);

    /**
     * Add \a data to send buffer.
     */
    void write(const ByteArray& data);

    /**
     * Add \a data to send buffer, and flush.
     */
    void send(const ByteArray& data);

    /**
     * Write all buffered data to the socket.
     */
    void flush();

    /**
     * Returns the current read timeout.
     */
    unsigned long getReadTimeout() const;

    /**
     * Set read timeout to \a msec milliseconds.
     *
     * If set, read calls will throw a TimeoutException if this number of
     * milliseconds elapses before data is received by the socket.
     */
    void setReadTimeout(unsigned long msec);

    /**
     * Returns the current write timeout.
     */
    unsigned long getWriteTimeout() const;

    /**
     * Set write timeout to \a msec milliseconds.
     *
     * If set, write calls will throw a TimeoutException if this number of
     * milliseconds elapses before data can be written to the socket.
     */
    void setWriteTimeout(unsigned long msec);


private:
    DISABLE_COPY(TCPSocket);

    // Constructor used by TCPServer::accept()
    TCPSocket(TCPSocketPrivate* data);

    TCPSocketPrivate* d;
};

} // namespace pcs

#endif // PIECES_TCP_SOCKET_H
