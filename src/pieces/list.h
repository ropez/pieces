#ifndef LIST_H
#define LIST_H

#include "PString"

#include <sstream>
#include <iomanip>
#include <vector>


class List
{
public:
    typedef std::vector<PString> PropertyList;

    List();
    ~List();

    int size() const;

    List& addValue(const PString& value);
    PString getValue(int index) const;

    template<typename T>
    List& add(const T& value);

    template<typename T>
    T get(int index) const;

    PropertyList::const_iterator begin() const;
    PropertyList::const_iterator end() const;

private:
    PropertyList m_data;
};

std::ostream& operator<<(std::ostream& os, const List& l);
std::istream& operator>>(std::istream& is, List& l);


template<typename T>
List& List::add(const T& value)
{
    std::stringstream ss;
    ss << value;

    return addValue(ss.str());
}

template<typename T>
T List::get(int index) const
{
    PString value = getValue(index);
    std::stringstream ss(value);

    T result;
    ss >> std::noskipws >> std::setw(value.length()) >> result;
    return result;
}


#endif // LIST_H
