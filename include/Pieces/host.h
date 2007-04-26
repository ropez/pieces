
#ifndef PIECES_HOST_H
#define PIECES_HOST_H

#include "Pieces/EventHandler"
#include "Pieces/Message"


namespace pcs
{
class EventLoop;
class ConnectionManager;
class GameDataSender;
class HostPrivate;

/**
 * \class Host
 * \brief Base class for host application.
 *
 * \author Robin Pedersen
 */
class Host : public EventHandler
{
public:
    Host();

    ~Host();

    EventLoop* eventLoop() const;

    /**
     * Start accepting incoming connections on the given port.
     *
     * Same as connectionManager()->startListening(port).
     */
    void startListening(port_t port);

    /**
     * Stop accepting connections.
     *
     * Same as connectionManager()->stopListening().
     */
    void stopListening();

    /**
     * Post an event to the event-loop.
     *
     * This is a shortcut for getEventLoop()->postEvent(e).
     *
     * \see EventLoop::postEvent()
     */
    void postEvent(Event* e);

    /**
     * Send a message to all peers.
     *
     * The message is added to a message history list, and sent on all
     * peers, even those that connect in the future.
     *
     * This is a shortcut for
     * \link
     * ConnectionManager::sendMessage(const Message&)
     * connectionManager()->sendMessage(message)
     * \endlink
     */
    msgid_t sendMessage(const Message& message);

    /**
     * Send a message to all peers.
     *
     * \overload
     *
     * The value of \a originalId must refer to a message previously sent,
     * and the result after sending these two messages must be equivalent
     * to not sending any of them.
     *
     * If a message with \a originalId is found in the message history, the
     * original message is removed instead of adding this message to the
     * history. This is used to avoid that the message history keeps growing
     * if something is switced back and forth between two states. For instance
     * if a game object is created and removed repeatedly. Instead of adding
     * a remove message to the message history, the create message is deleted.
     *
     * If no message is found with \a originalId, the result is equivalent to
     * calling the overload with one parameter. The message is added to the
     * history.
     *
     * This is a shortcut for
     * \link
     * ConnectionManager::sendMessage(const Message&, msgid_t)
     * connectionManager()->sendMessage(message, originalId)
     * \endlink
     */
    msgid_t sendMessage(const Message& message, msgid_t originalId);

    /**
     * Send create object command to all peers.
     *
     * This function does not create a GameObject instance in the host process.
     * The caller can do this if needed.
     */
    void sendCreateObject(objectid_t objectId, int objectType);

    /**
     * Send remove object command to all peers.
     */
    void sendRemoveObject(objectid_t objectId);

    void exec();

    void quit();

protected:

    /**
     * Returns a pointer to a connection manager interface.
     */
    ConnectionManager* connectionManager() const;

    GameDataSender* sender();

private:
    DISABLE_COPY(Host);

    HostPrivate* d;
};

} // namespace pcs

#endif // PIECES_HOST_H
