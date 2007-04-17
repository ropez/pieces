#ifndef PIECES_TCP_SENDER_THREAD_H
#define PIECES_TCP_SENDER_THREAD_H

#include "Pieces/global"
#include "OpenThreads/Thread"


namespace pcs
{
class TCPSocket;
class MessageQueue;
class TCPSenderThreadPrivate;


/**
 * \class TCPSenderThread
 * \brief Thread that sends messages.
 *
 * \author Robin Pedersen
 */
class TCPSenderThread : public OpenThreads::Thread
{
public:
    TCPSenderThread(TCPSocket* socket, MessageQueue* queue);
    ~TCPSenderThread();

    void abort();

protected:
    virtual void run();

private:
    DISABLE_COPY(TCPSenderThread);

    TCPSenderThreadPrivate* d;
};

} // namespace pcs

#endif // PIECES_TCP_SENDER_THREAD_H
