#include "Pieces/TCPReceiverThread"
#include "Pieces/Debug"
#include "Pieces/NetworkEvent"
#include "Pieces/DataStream"
#include "Pieces/TCPSocket"
#include "Pieces/EventLoop"
#include "Pieces/Exception"
#include "Pieces/TimeoutException"




namespace Pieces
{

TCPReceiverThread::TCPReceiverThread(TCPSocket* socket, EventLoop* eventLoop)
: OpenThreads::Thread()
, m_aborted(false)
, m_socket(socket)
, m_eventLoop(eventLoop)
{
}


TCPReceiverThread::~TCPReceiverThread()
{
    abort();
}


void TCPReceiverThread::abort()
{
    m_aborted = true;
    join();
}


void TCPReceiverThread::run()
{
    try
    {
        m_socket->setReadTimeout(1000);
        DataStream ds(m_socket);

        while (!m_aborted)
        {
            try
            {
                int type;
                ds >> type;

                ByteArray data;
                ds >> data;

                std::auto_ptr<Event> e(new NetworkEvent(type));
                e->setData(data);
                m_eventLoop->postEvent(e.release());
            }
            catch (const TimeoutException&)
            {
                // Ignore, try again
            }
        }
    }
    catch(const Exception& e)
    {
        ERROR << e;
    }
}

} // namespace Pieces
