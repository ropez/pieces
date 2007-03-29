#ifndef PIECES_TIMEOUT_EXCEPTION_H
#define PIECES_TIMEOUT_EXCEPTION_H

#include "Pieces/IOException"


namespace Pieces
{


/**
 * \class TimeoutException
 * \brief Input/output timeout exception class
 *
 * \author Thomas and Tord
 */
class TimeoutException : public IOException
{
public:
    TimeoutException();
    TimeoutException(const std::string& message);
    TimeoutException(const std::string& where, const std::string& message);

    virtual std::string getClassName() const;
};


} // namespace Pieces

#endif // PIECES_TIMEOUT_EXCEPTION_H
