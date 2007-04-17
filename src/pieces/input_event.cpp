
#include "Pieces/InputEvent"
#include "Pieces/EventHandler"


namespace pcs
{

InputEvent::InputEvent(int type)
: Event()
, m_type(type)
{
}


AutoPointer<Event> InputEvent::clone() const
{
    AutoPointer<InputEvent> event(new InputEvent(type()));

    return AutoPointer<Event>(event);
}


void InputEvent::dispatch(EventHandler* h)
{
    h->handle(this);
}


int InputEvent::type() const
{
    return m_type;
}


void InputEvent::setType(int type)
{
    m_type = type;
}


InputEvent::~InputEvent()
{
}

} // namespace pcs
