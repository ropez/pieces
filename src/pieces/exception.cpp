#include "Pieces/Exception"


namespace Pieces
{

Exception::Exception()
: m_where()
, m_message()
{
}


Exception::Exception(const std::string& message)
: m_where()
, m_message(message)
{
}


Exception::Exception(const std::string& where, const std::string& message)
: m_where(where)
, m_message(message)
{
}


Exception::~Exception()
{
}


std::string Exception::getClassName() const
{
    return "Exception";
}


std::string Exception::getWhere() const
{
    return m_where;
}


std::string Exception::getMessage() const
{
    return m_message;
}


std::ostream& operator<<(std::ostream& os, const Exception& e)
{
    os << e.getClassName();
    std::string where = e.getWhere();
    if (!where.empty())
    {
        os << "(in " << where << ")";
    }
    os << ": " << e.getMessage();

    return os;
}

};
