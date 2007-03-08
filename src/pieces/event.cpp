
#include "Pieces/Event"
#include "Pieces/EventHandler"


namespace Pieces
{

Event::Event(int type)
: m_type(type)
, m_data()
{
}


Event::~Event()
{
}


int Event::type() const
{
    return m_type;
}


bool Event::isUserDefined() const
{
    return type() >= USER_DEFINED;
}


void Event::setData(const ByteArray& data)
{
    m_data = data;
}


ByteArray Event::data() const
{
    return m_data;
}


void Event::trigger(EventHandler* h)
{
    h->handle(this);
}

} // namespace Pieces
