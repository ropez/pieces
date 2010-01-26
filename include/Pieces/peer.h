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

#ifndef PIECES_PEER_H
#define PIECES_PEER_H

#include "Pieces/EventHandler"


namespace pcs
{
class EventLoop;
class ConnectionManager;
class GameDataReceiver;
class SocketAddress;
class Message;
class PeerPrivate;


/**
 * \class Peer peer.h <Pieces/Peer>
 * \brief Base class for peer application.
 *
 * This is a base class that should be used by all applications acting as a peer
 * in a Pieces system.
 *
 * The peer contains an EventLoop that is started using exec(), and stopped
 * using quit(). The thread calling exec() will block until events are posted
 * to the host, and only wake up to call the appropriate event handler, until
 * quit() is called.
 *
 * The default peer implementation only provides default event handling functions
 * without any functionality. The user must create a subclass and implement all
 * needed event handlers.
 *
 * The peer provides an intarface connecting to a host, for using the Pieces
 * message system. Call connectTo() to set up a connection to a host. When
 * messages are received, the peer will receive a MessageReceivedEvent.
 *
 * The peer provides a GameDataReceiver for receiving game data from a host. This is
 * available through the receiver() function. When frame data arrives, the peer
 * will receive a GameDataEvent.
 *
 * \see Host
 * \author Robin Pedersen
 */
class Peer : public EventHandler
{
public:

    /**
     * Constructor.
     *
     * Initializes the peer.
     */
    Peer();

    /**
     * Destructor.
     *
     * Disconnects cleanly from the host, and releases all resources.
     */
    ~Peer();

    /**
     * Returns a pointer to the event loop.
     */
    EventLoop* eventLoop();

    /**
     * Connects the peer to the given host.
     *
     * Same as connectionManager()->connectTo(address).
     */
    void connectTo(const SocketAddress& address);

    /**
     * Post an event to the event-loop.
     *
     * This is a shortcut for eventLoop()->postEvent(e).
     *
     * \see EventLoop::postEvent()
     */
    void postEvent(Event* e);

    /**
     * Send a message to the host.
     *
     * The message is added to a message history list, and resent when a new
     * connection is established, in case the message is sent before a
     * connection is established to a host.
     *
     * This is a shortcut for
     * \link
     * ConnectionManager::sendMessage(const Message&)
     * connectionManager()->sendMessage(message)
     * \endlink
     */
    void sendMessage(const Message& message);

    /**
     * Enter the peer's main event loop.
     *
     * Call this function after connection to a host. The calling thread will
     * enter a loop where it handles events and sleeps while waiting for new ones.
     */
    void exec();

    /**
     * Quit the event loop.
     *
     * This will make exec() return after all event has been handled.
     */
    void quit();

protected:

    /**
     * Returns a pointer to a connection manager interface.
     */
    ConnectionManager* connectionManager() const;

    /**
     * Returns a pointer to the game data receiver.
     *
     * Use this in subclasses to call listen(). Incoming data will be given
     * as GameDataEvent.
     */
    GameDataReceiver* receiver();

private:
    DISABLE_COPY(Peer);

    PeerPrivate* d;
};

} // namespace pcs

#endif // PIECES_PEER_H
