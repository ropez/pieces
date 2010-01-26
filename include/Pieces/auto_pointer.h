/*
    Copyright 2007,2010 The Pieces Team

    This file is part of Pieces.

    Pieces is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Pieces is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
    more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Pieces.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PIECES_AUTO_POINTER_H
#define PIECES_AUTO_POINTER_H


namespace pcs
{


// This is for internal use only
template<typename Tp>
class _AutoPointerRef
{
public:
    _AutoPointerRef(Tp* ptr)
        : ptr(ptr) {}

    Tp* ptr;
};


/**
 * \class AutoPointer auto_pointer.h <Pieces/AutoPointer>
 * \brief Smart pointer that takes ownership of the object it points to.
 *
 * An auto-pointer \em owns the object it points to, and is responsible for
 * deleting it. An auto-pointer is simpler than a reference pointer, because
 * only one auto-pointer can point to an object. If the value of an auto-pointer
 * is assigned to another auto-pointer, the pointer assigned to becomes the new
 * owner of the object, and the original owner becones a null pointer.
 *
 * This class is identcal to the standard std::auto_ptr, except that it has
 * assignment operator that assigns from T* and some additional functions.
 *
 * All functions involving the _AutoPointerRef class is kind of a C++ hack.
 * It allows thing like creating an auto-pointer from the return value of a
 * function returning an auto pointer by value. This would not be possible
 * without this hack, since the class have no copy constructor that take a
 * const parameter:
 * \code
 * ReferencePointer<Subclass> foo();
 * // ...
 * ReferencePointer<Baseclass> ptr = foo();
 * \endcode
 *
 * This hack was copied from std::auto_ptr.
 *
 * \see \ref smart_pointers ReferencePointer
 * \author Robin Pedersen
 */
template<typename T>
class AutoPointer
{
public:

    /**
     * Typedef for the type pointed to.
     */
    typedef T element_type;

    /**
     * Creates a null (invalid) pointer.
     */
    AutoPointer();

    /**
     * Destructor.
     *
     * Deletes the object pointed to, if valid.
     */
    ~AutoPointer();

    /**
     * Create an auto-pointer that points to \a ptr.
     */
    AutoPointer(T* ptr);

    /**
     * Create an auto-pointer that points to the same as \a other.
     */
    AutoPointer(AutoPointer& other);

    /**
     * Create an auto-pointer that points to the same as \a ref.
     */
    AutoPointer(_AutoPointerRef<element_type> ref);

    /**
     * Make this auto-pointer point to \a ptr.
     */
    AutoPointer& operator=(T* ptr);

    /**
     * Make this auto-pointer point to the same as \a other.
     */
    AutoPointer& operator=(AutoPointer& other);

    /**
     * Make this auto-pointer point to the same as \a ref.
     */
    AutoPointer& operator=(_AutoPointerRef<element_type> other);

    /**
     * Returns a pointer to the object that this auto-pointer points to.
     */
    T* get() const;

    /**
     * Transfer ownership of the object to the caller.
     */
    T* release();

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
     * Automatic conversion to a "ref".
     */
    template<typename Tp>
    operator _AutoPointerRef<Tp>();

    /**
     * Automatic convertion to a related AutoPointer (baseclass).
     */
    template<typename Tp>
    operator AutoPointer<Tp>();

private:

    T* m_ptr;
};


/**
 * Comparison operator.
 *
 * \relates AutoPointer
 */
template<typename Tl, typename Tr>
bool operator==(const AutoPointer<Tl>& rp1, const AutoPointer<Tr>& rp2)
{
    return rp1.get() == rp2.get();
}


/**
 * Comparison operator.
 *
 * \relates AutoPointer
 */
template<typename Tl, typename Tr>
bool operator==(const AutoPointer<Tl>& rp, Tr* ptr)
{
    return rp.get() == ptr;
}


/**
 * Comparison operator.
 *
 * \relates AutoPointer
 */
template<typename Tl, typename Tr>
bool operator==(Tl* ptr, const AutoPointer<Tr>& rp)
{
    return ptr == rp.get();
}


/**
 * Comparison operator.
 *
 * \relates AutoPointer
 */
template<typename Tl, typename Tr>
bool operator!=(const AutoPointer<Tl>& rp1, const AutoPointer<Tr>& rp2)
{
    return rp1.get() != rp2.get();
}


/**
 * Comparison operator.
 *
 * \relates AutoPointer
 */
template<typename Tl, typename Tr>
bool operator!=(const AutoPointer<Tl>& rp, Tr* ptr)
{
    return rp.get() != ptr;
}


/**
 * Comparison operator.
 *
 * \relates AutoPointer
 */
template<typename Tl, typename Tr>
bool operator!=(Tl* ptr, const AutoPointer<Tr>& rp)
{
    return ptr != rp.get();
}



template<typename T>
AutoPointer<T>::AutoPointer()
: m_ptr(0)
{
}


template<typename T>
AutoPointer<T>::~AutoPointer()
{
    delete m_ptr;
}


template<typename T>
AutoPointer<T>::AutoPointer(T* ptr)
: m_ptr(ptr)
{
}


template<typename T>
AutoPointer<T>::AutoPointer(AutoPointer<T>& other)
: m_ptr(other.release())
{
}


template<typename T>
AutoPointer<T>::AutoPointer(_AutoPointerRef<element_type> ref)
: m_ptr(ref.ptr)
{
}


template<typename T>
AutoPointer<T>& AutoPointer<T>::operator=(T* ptr)
{
    if (m_ptr != ptr)
    {
        delete m_ptr;
        m_ptr = ptr;
    }
    return *this;
}


template<typename T>
AutoPointer<T>& AutoPointer<T>::operator=(AutoPointer& other)
{
    if (m_ptr != other.m_ptr)
    {
        delete m_ptr;
        m_ptr = other.release();
    }
    return *this;
}


template<typename T>
AutoPointer<T>& AutoPointer<T>::operator=(_AutoPointerRef<element_type> ref)
{
    if (m_ptr != ref.ptr)
    {
        delete m_ptr;
        m_ptr = ref.ptr;
    }
    return *this;
}


template<typename T>
T* AutoPointer<T>::get() const
{
    return m_ptr;
}


template<typename T>
T* AutoPointer<T>::release()
{
    T* tmp = m_ptr;
    m_ptr = 0;
    return tmp;
}


template<typename T>
T* AutoPointer<T>::operator->() const
{
    return m_ptr;
}


template<typename T>
T& AutoPointer<T>::operator*() const
{
    return *m_ptr;
}


template<typename T>
bool AutoPointer<T>::isValid() const
{
    return m_ptr != 0;
}


template<typename T>
bool AutoPointer<T>::isNull() const
{
    return m_ptr == 0;
}


template<typename T>
bool AutoPointer<T>::operator!() const
{
    return !m_ptr;
}


template<typename T> template<typename Tp>
AutoPointer<T>::operator _AutoPointerRef<Tp>()
{
    return _AutoPointerRef<Tp>(release());
}


template<typename T> template<typename Tp>
AutoPointer<T>::operator AutoPointer<Tp>()
{
    return AutoPointer<Tp>(release());
}

} // namespace pcs

#endif // PIECES_REFERENCE_POINTER_H
