
#include "Pieces/Event"
#include "Pieces/EventHandler"


namespace Pieces
{

Event::Data::Data()
: SharedData()
, type(0)
, data()
{
}


Event::Data::Data(const Data& other)
: SharedData()
, type(other.type)
, data(other.data)
{
}


Event::Event(int type)
: d(new Data)
{
    d->type = type;
}


Event::~Event()
{
}


int Event::type() const
{
    return d->type;
}


bool Event::isUserDefined() const
{
    return d->type >= USER_DEFINED;
}


void Event::setData(const ByteArray& data)
{
    d->data = data;
}


ByteArray Event::data() const
{
    return d->data;
}


void Event::trigger(EventHandler* h)
{
    h->handle(this);
}

} // namespace Pieces
