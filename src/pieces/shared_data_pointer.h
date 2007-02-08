
#ifndef PIECES_SHARED_DATA_POINTER_H
#define PIECES_SHARED_DATA_POINTER_H

namespace Pieces
{

template<class T>
class SharedDataPointer
{
public:

    SharedDataPointer();

    SharedDataPointer(T* ptr);

    SharedDataPointer(const SharedDataPointer<T>& other);

    ~SharedDataPointer();

    SharedDataPointer<T>& operator=(T* ptr);

    SharedDataPointer<T>& operator=(const SharedDataPointer<T>& other);

    T& operator*();

    const T& operator*() const;

    T* operator->();

    const T* operator->() const;

private:

    void ref();

    void deref();

    void detach();

    T* m_ptr;
};


template<class T>
SharedDataPointer<T>::SharedDataPointer()
: m_ptr(0)
{
}


template<class T>
SharedDataPointer<T>::SharedDataPointer(T* ptr)
: m_ptr(ptr)
{
    ref();
}


template<class T>
SharedDataPointer<T>::SharedDataPointer(const SharedDataPointer<T>& other)
: m_ptr(other.m_ptr)
{
    ref();
}


template<class T>
SharedDataPointer<T>::~SharedDataPointer()
{
    deref();
}


template<class T>
SharedDataPointer<T>& SharedDataPointer<T>::operator=(T* ptr)
{
    if (m_ptr != ptr)
    {
        deref();
        m_ptr = ptr;
        ref();
    }
}


template<class T>
SharedDataPointer<T>& SharedDataPointer<T>::operator=(const SharedDataPointer<T>& other)
{
    if (this != &other)
    {
        deref();
        m_ptr = other.m_ptr;
        ref();
    }
    return *this;
}


template<class T>
T& SharedDataPointer<T>::operator*()
{
    detach();
    return *m_ptr;
}


template<class T>
const T& SharedDataPointer<T>::operator*() const
{
    return *m_ptr;
}


template<class T>
T* SharedDataPointer<T>::operator->()
{
    detach();
    return m_ptr;
}


template<class T>
const T* SharedDataPointer<T>::operator->() const
{
    return m_ptr;
}


template<class T>
void SharedDataPointer<T>::ref()
{
    if (m_ptr)
    {
        m_ptr->ref();
    }
}


template<class T>
void SharedDataPointer<T>::deref()
{
    if (m_ptr && !m_ptr->deref())
    {
        delete m_ptr;
        m_ptr = 0;
    }
}


template<class T>
void SharedDataPointer<T>::detach()
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
    if (m_ptr->shared())
    {
        // We probably need a copy
        T* tmp = new T(*m_ptr);

        deref();
        m_ptr = tmp;
        ref();
    }
}


} // namespace Pieces

#endif // PIECES_SHARED_DATA_POINTER_H
