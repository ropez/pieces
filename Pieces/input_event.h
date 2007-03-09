
#ifndef PIECES_INPUT_EVENT_H
#define PIECES_INPUT_EVENT_H

#include "Pieces/Event"

namespace Pieces
{


/**
 * \class InputEvent
 * \brief Game-specific input event.
 *
 * This kind of event is created by peers as result of user input, and
 * propagated to the host by the framework.
 *
 * \author Robin Pedersen
 */
class InputEvent : public Event
{
public:

    /**
     * Creates an input-event and sets the type property to the given \a type.
     */
    explicit InputEvent(int type = 0);

    /**
     * Returns the event type.
     */
    int type() const;

    /**
     * Set or change the event type.
     */
    void setType(int type);

protected:
    virtual ~InputEvent();

    virtual void dispatch(EventHandler* h);

private:
    int m_type;
};

} // namespace Pieces

#endif // PIECES_INPUT_EVENT_H
