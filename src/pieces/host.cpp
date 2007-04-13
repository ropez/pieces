
#include "Pieces/Host"
#include "Pieces/Debug"
#include "Pieces/EventLoop"
#include "Pieces/GameDataSender"
#include "Pieces/TCPConnectionManager"

#include "NetworkEventFilter"



namespace Pieces
{

class HostPrivate
{
public:
    HostPrivate();

    AutoPointer<EventLoop> eventLoop;
    AutoPointer<TCPConnectionManager> connectionManager;
    AutoPointer<GameDataSender> sender;

    AutoPointer<NetworkEventFilter> networkEventFilter;

    std::map<objectid_t, msgid_t> createMessageIds;
};


HostPrivate::HostPrivate()
: eventLoop(0)
, connectionManager(0)
, sender(0)
, networkEventFilter(0)
, createMessageIds()
{
}


Host::Host()
: EventHandler()
, d(new HostPrivate)
{
    d->eventLoop = new EventLoop();
    d->connectionManager = new TCPConnectionManager(eventLoop());
    d->networkEventFilter = new NetworkEventFilter(this, d->connectionManager.get());
}


Host::~Host()
{
    delete d;
}


EventLoop* Host::eventLoop() const
{
    return d->eventLoop.get();
}


void Host::startListening(port_t port)
{
    connectionManager()->startListening(port);
}


void Host::stopListening()
{
    connectionManager()->stopListening();
}


void Host::postEvent(Event* e)
{
    eventLoop()->postEvent(e);
}


msgid_t Host::sendMessage(const Message& message)
{
    return connectionManager()->sendMessage(message);
}


msgid_t Host::sendMessage(const Message& message, msgid_t originalId)
{
    return connectionManager()->sendMessage(message, originalId);
}


void Host::sendCreateObject(objectid_t objectId, int objectType)
{
    Message message(OBJECT_CREATE, Message::FL_PERMANENT);
    message.set(PR_OBJECT_TYPE, objectType);
    message.set(PR_OBJECT_ID, objectId);

    msgid_t msgid = sendMessage(message);
    d->createMessageIds[objectId] = msgid;
}


void Host::sendRemoveObject(objectid_t objectId)
{
    Message message(OBJECT_REMOVE, Message::FL_PERMANENT);
    message.set(PR_OBJECT_ID, objectId);

    if (d->createMessageIds.find(objectId) != d->createMessageIds.end())
    {
        sendMessage(message, d->createMessageIds[objectId]);
        d->createMessageIds.erase(objectId);
    }
    else
    {
        sendMessage(message);
    }
}


void Host::exec()
{
    PDEBUG << "Host running";
    eventLoop()->exec(d->networkEventFilter.get());
}


void Host::quit()
{
    PDEBUG << "Host quitting";
    eventLoop()->quit();
}


ConnectionManager* Host::connectionManager() const
{
    return d->connectionManager.get();
}


GameDataSender* Host::sender()
{
    // Lazy instantiation
    if (d->sender.isNull())
    {
        d->sender = new GameDataSender();
    }
    return d->sender.get();
}


void Host::peerConnected(PeerInfo* /*info*/)
{
    // TODO: Anything to do if user haven't implemented this?
}


void Host::peerDisconnected(PeerInfo* /*info*/)
{
    // TODO: Anything to do if user haven't implemented this?
}

} // namespace Pieces
