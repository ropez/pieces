
#ifndef PIECES_REFERENCE_POINTER_H
#define PIECES_REFERENCE_POINTER_H


namespace Pieces
{

template<class T>
class ReferencePointer
{
public:
    ReferencePointer();
    ~ReferencePointer();

    ReferencePointer(T* ptr);
    ReferencePointer(const ReferencePointer& other);

    ReferencePointer& operator=(T* ptr);
    ReferencePointer& operator=(const ReferencePointer& other);

    T* get();
    const T* get() const;

    T* operator->();

private:
    void ref();
    void deref();

    T* m_ptr;
};



template<class T>
ReferencePointer<T>::ReferencePointer()
: m_ptr(0)
{
}


template<class T>
ReferencePointer<T>::~ReferencePointer()
{
    deref();
}


template<class T>
ReferencePointer<T>::ReferencePointer(T* ptr)
: m_ptr(ptr)
{
    ref();
}


template<class T>
ReferencePointer<T>::ReferencePointer(const ReferencePointer& other)
: m_ptr(other.m_ptr)
{
    ref();
}


template<class T>
ReferencePointer<T>& ReferencePointer<T>::operator=(T* ptr)
{
    if (m_ptr != ptr)
    {
        deref();
        m_ptr = ptr;
        ref();
    }
    return *this;
}


template<class T>
ReferencePointer<T>& ReferencePointer<T>::operator=(const ReferencePointer& other)
{
    if (m_ptr != other.m_ptr)
    {
        deref();
        m_ptr = other.m_ptr;
        ref();
    }
    return *this;
}


template<class T>
T* ReferencePointer<T>::get()
{
    return m_ptr;
}


template<class T>
const T* ReferencePointer<T>::get() const
{
    return m_ptr;
}


template<class T>
void ReferencePointer<T>::ref()
{
    if (m_ptr)
    {
        m_ptr->ref();
    }
}


template<class T>
T* ReferencePointer<T>::operator->()
{
    return m_ptr;
}


template<class T>
void ReferencePointer<T>::deref()
{
    if (m_ptr)
    {
        if (!m_ptr->deref())
        {
            delete m_ptr;
            m_ptr = 0;
        }
    }
}

} // namespace Pieces

#endif // PIECES_REFERENCE_POINTER_H
