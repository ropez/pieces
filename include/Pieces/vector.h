
#ifndef PIECES_VECTOR_H
#define PIECES_VECTOR_H

#include "Pieces/SharedData"
#include "Pieces/SharedDataPointer"

#include <vector>

namespace pcs
{

template<typename T>
class Vector
{
public:
    typedef std::vector<T> stl_vector_t;
    typedef typename stl_vector_t::value_type value_type;
    typedef typename stl_vector_t::pointer pointer;
    typedef typename stl_vector_t::reference reference;
    typedef typename stl_vector_t::const_reference const_reference;
    typedef typename stl_vector_t::size_type size_type;
    typedef typename stl_vector_t::difference_type difference_type;
    typedef typename stl_vector_t::iterator iterator;
    typedef typename stl_vector_t::const_iterator const_iterator;
    typedef typename stl_vector_t::reverse_iterator reverse_iterator;
    typedef typename stl_vector_t::const_reverse_iterator const_reverse_iterator;

    Vector();
    Vector(size_type n);
    Vector(size_type n, const T& val);
    Vector(const Vector& other);
    Vector(const stl_vector_t& other);

    template <class InputIterator>
    Vector(InputIterator f, InputIterator l);

    ~Vector();

    Vector& operator=(const Vector& other);
    Vector& operator=(const stl_vector_t& other);

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;

    size_type size() const;
    size_type max_size() const;
    size_type capacity() const;
    bool empty() const;
    reference operator[](size_type n);
    const_reference operator[](size_type n) const;
    void reserve(size_t);
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    void push_back(const T& val);
    void pop_back();
    iterator insert(iterator pos, const T& val);
    template <class InputIterator>
    void insert(iterator pos, InputIterator f, InputIterator l);
    void insert(iterator pos, size_type n, const T& val);
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);
    void clear();

    void append(const T& val);

private:

    class Data : public SharedData
    {
    public:
        Data();
        Data(const Data& other);
        Data(const stl_vector_t& other);

        Data(size_type n);
        Data(size_type n, const T& val);

        template <class InputIterator>
        Data(InputIterator f, InputIterator l);

        Data& operator=(const Data& other);

        stl_vector_t data;

    protected:

        friend class SharedDataPointer<Data>;

        ~Data();
    };

    SharedDataPointer<Data> d;
};


template<typename T>
Vector<T>::Vector()
: d(new Data)
{
}


template<typename T>
Vector<T>::Vector(size_type n)
: d(new Data(n))
{
}


template<typename T>
Vector<T>::Vector(size_type n, const T& val)
: d(new Data(n, val))
{
}


template<typename T>
Vector<T>::Vector(const Vector& other)
: d(other.d)
{
}


template<typename T>
Vector<T>::Vector(const stl_vector_t& other)
: d(new Data(other))
{
}


template<typename T>
template<class InputIterator>
Vector<T>::Vector(InputIterator f, InputIterator l)
: d(new Data(f, l))
{
}


template<typename T>
Vector<T>::~Vector()
{
}


template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other)
{
    d = other.d;
    return *this;
}


template<typename T>
Vector<T>& Vector<T>::operator=(const stl_vector_t& other)
{
    d = new Data(other);
    return *this;
}


template<typename T>
typename Vector<T>::iterator
Vector<T>::begin()
{
    return d->data.begin();
}


template<typename T>
typename Vector<T>::iterator
Vector<T>::end()
{
    return d->data.end();
}


template<typename T>
typename Vector<T>::const_iterator
Vector<T>::begin() const
{
    return d->data.begin();
}


template<typename T>
typename Vector<T>::const_iterator
Vector<T>::end() const
{
    return d->data.end();
}


template<typename T>
typename Vector<T>::reverse_iterator
Vector<T>::rbegin()
{
    return d->data.rbegin();
}


template<typename T>
typename Vector<T>::reverse_iterator
Vector<T>::rend()
{
    return d->data.rend();
}


template<typename T>
typename Vector<T>::const_reverse_iterator
Vector<T>::rbegin() const
{
    return d->data.rbegin();
}


template<typename T>
typename Vector<T>::const_reverse_iterator
Vector<T>::rend() const
{
    return d->data.rend();
}


template<typename T>
typename Vector<T>::size_type
Vector<T>::size() const
{
    return d->data.size();
}


template<typename T>
typename Vector<T>::size_type
Vector<T>::max_size() const
{
    return d->data.max_size();
}


template<typename T>
typename Vector<T>::size_type
Vector<T>::capacity() const
{
    return d->data.capacity();
}


template<typename T>
bool Vector<T>::empty() const
{
    return d->data.empty();
}


template<typename T>
typename Vector<T>::reference
Vector<T>::operator[](size_type n)
{
    return d->data[n];
}


template<typename T>
typename Vector<T>::const_reference
Vector<T>::operator[](size_type n) const
{
    return d->data[n];
}


template<typename T>
void Vector<T>::reserve(size_t n)
{
    return d->data.reserve(n);
}


template<typename T>
typename Vector<T>::reference
Vector<T>::front()
{
    return d->data.front();
}


template<typename T>
typename Vector<T>::const_reference
Vector<T>::front() const
{
    return d->data.front();
}


template<typename T>
typename Vector<T>::reference
Vector<T>::back()
{
    return d->data.back();
}


template<typename T>
typename Vector<T>::const_reference
Vector<T>::back() const
{
    return d->data.back();
}


template<typename T>
void Vector<T>::push_back(const T& val)
{
    return d->data.push_back(val);
}


template<typename T>
void Vector<T>::pop_back()
{
    return d->data.pop_back();
}


template<typename T>
typename Vector<T>::iterator
Vector<T>::insert(iterator pos, const T& val)
{
    return d->data.insert(pos, val);
}


template<typename T>
template<class InputIterator>
void Vector<T>::insert(iterator pos, InputIterator f, InputIterator l)
{
    return d->data.insert(pos, f, l);
}


template<typename T>
void Vector<T>::insert(iterator pos, size_type n, const T& val)
{
    return d->data.insert(pos, n, val);
}


template<typename T>
typename Vector<T>::iterator
Vector<T>::erase(iterator pos)
{
    return d->data.erase(pos);
}


template<typename T>
typename Vector<T>::iterator
Vector<T>::erase(iterator first, iterator last)
{
    return d->data.erase(first, last);
}


template<typename T>
void Vector<T>::clear()
{
    return d->data.clear();
}


template<typename T>
void Vector<T>::append(const T& val)
{
    push_back(val);
}


template<typename T>
Vector<T>::Data::Data()
: SharedData()
, data()
{
}


template<typename T>
Vector<T>::Data::Data(const Data& other)
: SharedData()
, data(other.data)
{
}


template<typename T>
Vector<T>::Data::Data(const stl_vector_t& other)
: SharedData()
, data(other)
{
}


template<typename T>
Vector<T>::Data::Data(size_type n)
: SharedData()
, data(n)
{
}


template<typename T>
Vector<T>::Data::Data(size_type n, const T& val)
: SharedData()
, data(n, val)
{
}


template<typename T>
template<class InputIterator>
Vector<T>::Data::Data(InputIterator f, InputIterator l)
: SharedData()
, data(f, l)
{
}


template<typename T>
typename Vector<T>::Data& Vector<T>::Data::operator=(const Data& other)
{
    data = other.data;
    return *this;
}


template<typename T>
Vector<T>::Data::~Data()
{
}

} // namespace pcs

#endif // PIECES_VECTOR_H
