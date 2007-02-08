
#include "byte_array.h"
#include "atomic.h"

#include <algorithm>

namespace Pieces
{

class ByteArrayData
{
public:
    int size;
    char* data;

    unsigned int ref_count;
};


ByteArray::ByteArray()
: d(new ByteArrayData)
{
    d->size = 0;
    d->data = new char[0];
    d->ref_count = 1;
}


ByteArray::ByteArray(const char* data, int size)
: d(new ByteArrayData)
{
    d->size = size;
    d->data = new char[size];
    std::copy(data, data + size, d->data);
    d->ref_count = 1;
}


ByteArray::ByteArray(const ByteArray& other)
: d(other.d)
{
    atomic_increment(&d->ref_count);
}


ByteArray& ByteArray::operator=(const ByteArray& other)
{
    if (this != &other)
    {
        if (!atomic_decrement(&d->ref_count))
        {
            delete d;
            d = 0;
        }

        d = other.d;
        atomic_increment(&d->ref_count);
    }
    return *this;
}


int ByteArray::size() const
{
    return d->size;
}


char* ByteArray::data()
{
    detach();
    return d->data;
}


const char* ByteArray::data() const
{
    return d->data;
}


void ByteArray::detach()
{
    // NOTE: Testing the reference count isn't thread safe. However, the
    // operations done inside the body is always safe to do, even if another
    // thread decreases refcount. Worst case scenario is that we create a copy
    // when we really don't need one.
    //
    // Second scenario: What if the refcount is 1, and we decide not to make a
    // copy, and the refcount is increased by another thread. This implies that
    // the other thread makes a copy of *this* array. That's the user's
    // responsibility.

    // Only make a deep copy if data is shared by more than one array
    if (d->ref_count > 1)
    {
        // We probably need a copy
        ByteArrayData* tmp = d;
        d = new ByteArrayData;
        d->size = tmp->size;
        d->data = new char[tmp->size];
        std::copy(tmp->data, tmp->data + tmp->size, d->data);
        d->ref_count = 1;

        // Decrease ref counter to previously shared data
        if (!atomic_decrement(&tmp->ref_count))
        {
            delete tmp;
            tmp = 0;
        }
    }
}

} // namespace Pieces

