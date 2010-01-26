/*
    Copyright 2007,2010 The Pieces Team

    This file is part of Pieces.

    Pieces is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Pieces is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
    more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Pieces.  If not, see <http://www.gnu.org/licenses/>.
*/

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
 * \class Host host.h <Pieces/Host>
 * \brief Base class for host application.
 *
 * This is a base class that should be used by all applications acting as a host
 * in a Pieces system.
 *
 * The host contains an EventLoop that is started using exec(), and stopped
 * using quit(). The thread calling exec() will block until events are posted
 * to the host, and only wake up to call the appropriate event handler, until
 * quit() is called.
 *
 * The default host implementation only provides default event handling functions
 * without any functionality. The user must create a subclass and implement all
 * needed event handlers.
 *
 * The host provides an intarface for listening for incoming connections, for using
 * the Pieces message system. Call startListening() to start the server of a
 * given port, and stopListening() to stop it. When messages are received, the
 * host will receive a MessageReceivedEvent.
 *
 * The host provides a GameDataSender for transfering game data to peers. This is
 * available through the sender() function.
 *
 * \see Peer
 * \author Robin Pedersen
 */
class Host : public EventHandler
{
public:

    /**
     * Constructor.
     *
     * Initializes the host.
     */
    Host();

    /**
     * Destructor.
     *
     * Disconnects cleanly from all peers, and releases all resources.
     */
    ~Host();

    /**
     * Returns a pointer to the event loop.
     */
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

    /**
     * Executes the host's event loop.
     *
     * Same as \link EventLoop::exec eventLoop()->exec() \endlink.
     */
    void exec();

    /**
     * Quits the host's event loop.
     *
     * Same as \link EventLoop::quit eventLoop()->quit() \endlink.
     */
    void quit();

protected:

    /**
     * Returns a pointer to a connection manager interface.
     */
    ConnectionManager* connectionManager() const;

    /**
     * Returns a pointer to the game data sender.
     *
     * Use this in subclasses to call sendFrameData().
     */
    GameDataSender* sender();

private:
    DISABLE_COPY(Host);

    HostPrivate* d;
};

} // namespace pcs

#endif // PIECES_HOST_H
