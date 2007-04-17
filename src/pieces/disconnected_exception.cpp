#include "Pieces/DisconnectedException"


namespace pcs
{

DisconnectedException::DisconnectedException()
: Exception()
{
}


DisconnectedException::DisconnectedException(const std::string& message)
: Exception(message)
{
}


DisconnectedException::DisconnectedException(const std::string& where, const std::string& message)
: Exception(where, message)
{
}


std::string DisconnectedException::getClassName() const
{
    return "DisconnectedException";
}

} // namespace pcs
