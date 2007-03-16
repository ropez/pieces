#include "Pieces/TimeoutException"


namespace Pieces
{

TimeoutException::TimeoutException()
: IOException()
{
}


TimeoutException::TimeoutException(const std::string& message)
: IOException(message)
{
}


TimeoutException::TimeoutException(const std::string& where, const std::string& message)
: IOException(where, message)
{
}


std::string TimeoutException::getClassName() const
{
    return "TimeoutException";
}

} // namespace Pieces
