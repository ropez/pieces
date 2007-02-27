
#include "Pieces/TCPServer"

namespace Pieces
{

TCPServer::TCPServer()
{

}

TCPServer::~TCPServer()
{

}

void TCPServer::bind(const InetAddress& addr)
{

}

// or maybe just listen(addr) ????
void TCPServer::listen()
{

}

int TCPServer::getQueueSize() const
{

}

void TCPServer::setQueueSize(int size)
{

}

// Caller must delete this (maybe use auto_ptr?)
TCPSocket* TCPServer::accept()
{

}


} // namespace Pieces
