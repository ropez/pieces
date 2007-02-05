#ifndef LIST_H
#define LIST_H

#include "String"
#include "PropertyList"

class List
{
public:
    List();
    ~List();

    int size() const;

    List& addValue(const String& value);
    String getValue(int index) const;

    PropertyList::const_iterator begin() const;
    PropertyList::const_iterator end() const;

private:
    PropertyList m_data;
};

std::ostream& operator<<(std::ostream& os, const List& l);
std::istream& operator>>(std::istream& is, List& l);

#endif // LIST_H
