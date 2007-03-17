#ifndef PIECES_DISCONNECTED_EXCEPTION_H
#define PIECES_DISCONNECTED_EXCEPTION_H

#include "Pieces/Exception"


namespace Pieces
{


/**
 * \class DisconnectedException
 * \brief Input/output exception class
 *
 * \author Thomas and Tord
 */
class DisconnectedException : public Exception
{
public:
    DisconnectedException();
    DisconnectedException(const std::string& message);
    DisconnectedException(const std::string& where, const std::string& message);

    virtual std::string getClassName() const;
};


} // namespace Pieces

#endif // PIECES_DISCONNECTED_EXCEPTION_H
