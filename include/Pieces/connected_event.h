
#ifndef PIECES_CONNECTED_EVENT_H
#define PIECES_CONNECTED_EVENT_H

#include "Pieces/NetworkEvent"


namespace Pieces
{

/**
 * \class ConnectedEvent
 * \brief A network-connect event.
 *
 * \author Tord Heimdal
 */
class ConnectedEvent : public NetworkEvent
{
    friend class AutoPointer<ConnectedEvent>;

public:

    /**
     * Constructor.
     */
    ConnectedEvent(const SocketAddress& sender);

public:

    virtual AutoPointer<Event> clone() const;
    virtual void dispatch(EventHandler* h);

protected:

    virtual ~ConnectedEvent();


private:
    DISABLE_COPY(ConnectedEvent);
};

} // namespace Pieces

#endif // PIECES_CONNECTED_EVENT_H
