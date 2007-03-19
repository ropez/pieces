
#ifndef PIECES_NETWORK_EVENT_H
#define PIECES_NETWORK_EVENT_H

#include "Pieces/Event"

namespace Pieces
{


/**
 * \class NetworkEvent
 * \brief A network-specific event.
 *
 * 
 *
 *
 * \author Tord Heimdal
 */
class NetworkEvent : public Event
{
public:

    /**
     * .
     */
    explicit NetworkEvent(int type = 0);

    /**
     * Returns the event type.
     */
    int type() const;

    /**
     * Set or change the event type.
     */
    void setType(int type);

protected:
    virtual ~NetworkEvent();

    virtual void dispatch(EventHandler* h);

private:
    int m_type;
};

} // namespace Pieces

#endif // PIECES_NETWORK_EVENT_H
