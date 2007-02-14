
#ifndef PIECES_VECTOR_H
#define PIECES_VECTOR_H

#include "SharedData"
#include "SharedDataPointer"

#include <vector>

namespace Pieces
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

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    reverse_iterator rbegin();
    reverse_iterator rend();
    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;

    void append(const T& val);

    T& operator[](int index);
    const T& operator[](int index) const;

private:

    class Data : public SharedData
    {
    public:
        Data();
        Data(const Data& other);
        Data& operator=(const Data& other);

        std::vector<T> data;

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
typename Vector<T>::iterator Vector<T>::begin()
{
    return d->data.begin();
}


template<typename T>
typename Vector<T>::iterator Vector<T>::end()
{
    return d->data.end();
}


template<typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const
{
    return d->data.begin();
}


template<typename T>
typename Vector<T>::const_iterator Vector<T>::end() const
{
    return d->data.end();
}


template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::rbegin()
{
    return d->data.rbegin();
}


template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::rend()
{
    return d->data.rend();
}


template<typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::rbegin() const
{
    return d->data.rbegin();
}


template<typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::rend() const
{
    return d->data.rend();
}


template<typename T>
void Vector<T>::append(const T& val)
{
    d->data.push_back(val);
}


template<typename T>
T& Vector<T>::operator[](int index)
{
    return d->data[index];
}


template<typename T>
const T& Vector<T>::operator[](int index) const
{
    return d->data[index];
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
typename Vector<T>::Data& Vector<T>::Data::operator=(const Data& other)
{
    data = other.data;
    return *this;
}


template<typename T>
Vector<T>::Data::~Data()
{
}

} // namespace Pieces

#endif // PIECES_VECTOR_H
