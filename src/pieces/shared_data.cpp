
#include "Pieces/SharedData"
#include "atomic.h"


namespace pcs
{

bool SharedData::shared() const
{
    return m_count > 1;
}


bool SharedData::ref()
{
    return atomic_increment(&m_count);
}


bool SharedData::deref()
{
    return atomic_decrement(&m_count);
}


SharedData::SharedData()
: m_count(0)
{
}


SharedData::~SharedData()
{
}

} // namespace pcs
