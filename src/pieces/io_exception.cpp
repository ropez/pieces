#include "Pieces/IOException"


namespace pcs
{

IOException::IOException()
: Exception()
{
}


IOException::IOException(const std::string& message)
: Exception(message)
{
}


IOException::IOException(const std::string& where, const std::string& message)
: Exception(where, message)
{
}


std::string IOException::getClassName() const
{
    return "IOException";
}

} // namespace pcs
