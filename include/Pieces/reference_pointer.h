
#ifndef PIECES_REFERENCE_POINTER_H
#define PIECES_REFERENCE_POINTER_H


namespace pcs
{


/**
 * \class ReferencePointer reference_pointer.h <Pieces/ReferencePointer>
 * \brief Smart pointer for handling referenced counted objects.
 *
 * A reference pointer acts like a normal pointer, but it increases a reference
 * counter in the object it's pointing to, and descreases it when it stops
 * pointing to the object. If the reference counter becomes 0, the object
 * is deleted.
 *
 * The class T that the pointer points to must be a subclass of SharedData.
 *
 * \see \ref smart_pointers AutoPointer
 * \author Robin Pedersen
 */
template<class T>
class ReferencePointer
{
public:

    /**
     * Typedef for the type pointed to.
     */
    typedef T element_type;

    /**
     * Creates a null (invalid) pointer.
     */
    ReferencePointer();

    /**
     * Destructor.
     */
    ~ReferencePointer();

    /**
     * Create a reference pointer that points to \a ptr.
     */
    ReferencePointer(T* ptr);

    /**
     * Create a reference pointer that points to the same as \a other.
     */
    ReferencePointer(const ReferencePointer& other);

    /**
     * Make this reference pointer point to \a ptr.
     */
    ReferencePointer& operator=(T* ptr);

    /**
     * Make this reference pointer point to the same as \a other.
     */
    ReferencePointer& operator=(const ReferencePointer& other);

    /**
     * Returns a pointer to the object that this reference pointer points to.
     */
    T* get() const;

    /**
     * Operator used to access members in the object pointed to.
     *
     * This is used just like a normal pointer.
     */
    T* operator->() const;

    /**
     * Returns a reference to the object pointed to.
     *
     * This is used just like a normal pointer.
     */
    T& operator*() const;

    /**
     * Returns true if the pointer is not a null pointer.
     */
    bool isValid() const;

    /**
     * Returns true if the pointer is a null pointer.
     */
    bool isNull() const;

    /**
     * Returns true if the pointer is a null pointer.
     *
     * \see isNull()
     */
    bool operator!() const;

    /**
     * Automatic conversion to a reference pointer of a related type.
     */
    template<typename Tp>
    operator ReferencePointer<Tp>();

private:
    void ref();
    void deref();

    T* m_ptr;
};


/**
 * Comparison operator.
 *
 * \relates ReferencePointer
 */
template<class Tl, class Tr>
bool operator==(const ReferencePointer<Tl>& rp1, const ReferencePointer<Tr>& rp2)
{
    return rp1.get() == rp2.get();
}


/**
 * Comparison operator.
 *
 * \relates ReferencePointer
 */
template<class Tl, class Tr>
bool operator==(const ReferencePointer<Tl>& rp, Tr* ptr)
{
    return rp.get() == ptr;
}


/**
 * Comparison operator.
 *
 * \relates ReferencePointer
 */
template<class Tl, class Tr>
bool operator==(Tl* ptr, const ReferencePointer<Tr>& rp)
{
    return ptr == rp.get();
}


/**
 * Comparison operator.
 *
 * \relates ReferencePointer
 */
template<class Tl, class Tr>
bool operator!=(const ReferencePointer<Tl>& rp1, const ReferencePointer<Tr>& rp2)
{
    return rp1.get() != rp2.get();
}


/**
 * Comparison operator.
 *
 * \relates ReferencePointer
 */
template<class Tl, class Tr>
bool operator!=(const ReferencePointer<Tl>& rp, Tr* ptr)
{
    return rp.get() != ptr;
}


/**
 * Comparison operator.
 *
 * \relates ReferencePointer
 */
template<class Tl, class Tr>
bool operator!=(Tl* ptr, const ReferencePointer<Tr>& rp)
{
    return ptr != rp.get();
}



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
T* ReferencePointer<T>::get() const
{
    return m_ptr;
}


template<class T>
T* ReferencePointer<T>::operator->() const
{
    return m_ptr;
}


template<class T>
T& ReferencePointer<T>::operator*() const
{
    return *m_ptr;
}


template<class T>
bool ReferencePointer<T>::isValid() const
{
    return m_ptr != 0;
}


template<class T>
bool ReferencePointer<T>::isNull() const
{
    return m_ptr == 0;
}


template<class T>
bool ReferencePointer<T>::operator!() const
{
    return !m_ptr;
}


template<class T> template<class Tp>
ReferencePointer<T>::operator ReferencePointer<Tp>()
{
    return ReferencePointer<Tp>(m_ptr);
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

} // namespace pcs

#endif // PIECES_REFERENCE_POINTER_H
