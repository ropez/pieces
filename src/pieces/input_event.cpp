
#include "Pieces/InputEvent"
#include "Pieces/EventHandler"


namespace Pieces
{

InputEvent::InputEvent(int type)
: Event()
, m_type(type)
{
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


void InputEvent::dispatch(EventHandler* h)
{
    h->handle(this);
}

} // namespace Pieces
