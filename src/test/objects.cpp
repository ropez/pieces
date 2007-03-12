
#include "Pieces/SharedData"
#include "Pieces/SharedDataPointer"
#include "Pieces/ValueList"
#include "Pieces/Debug"


#include <map>


namespace Pieces
{

class PropertyType
{
public:
    PropertyType();

private:
    class Data : public SharedData
    {
    public:
        Data();

        int id;
        std::string description;
    };
    SharedDataPointer<Data> d;
};


PropertyType::PropertyType()
: d(new Data)
{
}


PropertyType::Data::Data()
: id(0)
, description()
{
}


class ObjectType
{
public:
    ObjectType();

private:
    class Data : public SharedData
    {
    public:
        std::map<int, PropertyType> properties;
    };

    SharedDataPointer<Data> d;
};


ObjectType::ObjectType()
: d(new Data)
{
}


class ObjectData
{
public:
    ObjectData();

private:
    class Data : public SharedData
    {
    public:
        ObjectType def;
        ValueList values;
    };

    SharedDataPointer<Data> d;
};


ObjectData::ObjectData()
: d(new Data)
{
}

} // namespace Pieces


int main()
{
    using namespace Pieces;

    DEBUG << "Hello";

    ObjectData d;
}

