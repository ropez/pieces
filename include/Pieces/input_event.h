
#ifndef PIECES_INPUT_EVENT_H
#define PIECES_INPUT_EVENT_H

#include "Pieces/Event"

namespace pcs
{


/**
 * \class InputEvent input_event.h <Pieces/InputEvent>
 * \brief Game-specific input event.
 *
 * \deprecated Use MessageReceivedEvent instead.
 *
 * This kind of event is created by peers as result of user input, and
 * propagated to the host by the framework.
 *
 * \author Robin Pedersen
 */
class InputEvent : public Event
{
    friend class AutoPointer<InputEvent>;

public:

    /**
     * Creates an input-event and sets the type property to the given \a type.
     */
    explicit InputEvent(int type = 0);

    /**
     * Returns a deep copy of this event.
     */
    virtual AutoPointer<Event> clone() const;

    /**
     * Calls h->handle(this).
     */
    virtual void dispatch(EventHandler* h);

    /**
     * Returns the event type.
     */
    int type() const;

    /**
     * Set or change the event type.
     */
    void setType(int type);

protected:

    /**
     * Protected destructor prevents stack allocation.
     */
    virtual ~InputEvent();

private:
    DISABLE_COPY(InputEvent);
    int m_type;
};

} // namespace pcs

#endif // PIECES_INPUT_EVENT_H
