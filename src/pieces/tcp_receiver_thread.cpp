#include "Pieces/TCPReceiverThread"
#include "Pieces/Debug"
#include "Pieces/NetworkEvent"
#include "Pieces/DataStream"
#include "Pieces/TCPSocket"
#include "Pieces/EventLoop"
#include "Pieces/Exception"




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
    try
    {
        DataStream ds(m_socket);

        for(;;)
        {
            int type;
            ds >> type;

            ByteArray data;
            ds >> data;

            std::auto_ptr<Event> e(new NetworkEvent(type));
            e->setData(data);
            m_eventLoop->postEvent(e.release());
        }
    }
    catch(const Exception& e)
    {
        ERROR << e;
    }
}

} // namespace Pieces
