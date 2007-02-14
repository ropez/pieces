
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
    Vector();

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
