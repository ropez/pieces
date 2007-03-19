#include "Pieces/TCPReceiverThread"
#include "Pieces/Debug"




namespace Pieces
{

TCPReceiverThread::TCPReceiverThread(TCPSocket* socket, EventLoop* eventLoop)
: OpenThreads::Thread()
, m_socket(socket)
, m_eventLoop(eventLoop)
{
}


void TCPReceiverThread::run()
{
    DEBUG << "Hei.";
}

} // namespace Pieces
