
#include "Pieces/InvalidKeyException"


namespace Pieces
{

InvalidKeyException::InvalidKeyException()
: Exception()
{
}


InvalidKeyException::InvalidKeyException(const std::string& message)
: Exception(message)
{
}


InvalidKeyException::InvalidKeyException(const std::string& where, const std::string& message)
: Exception(where, message)
{
}


std::string InvalidKeyException::getClassName() const
{
    return "InvalidKeyException";
}

} // namespace Pieces
