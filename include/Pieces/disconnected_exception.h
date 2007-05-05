#ifndef PIECES_DISCONNECTED_EXCEPTION_H
#define PIECES_DISCONNECTED_EXCEPTION_H

#include "Pieces/Exception"


namespace pcs
{


/**
 * \class DisconnectedException disconnected_exception.h <Pieces/DisconnectedException>
 * \brief Input/output exception class.
 *
 * This type of exception is thrown when a TCPSocket is disconnected while
 * operation is performed on it.
 *
 * \author Thomas Bakken, Tord Heimdal
 */
class DisconnectedException : public Exception
{
public:

    /**
     * Default constructor.
     */
    DisconnectedException();

    /**
     * Constructor that takes a message.
     */
    DisconnectedException(const std::string& message);

    /**
     * Constructor that takes a function name and a message.
     */
    DisconnectedException(const std::string& where, const std::string& message);

    /**
     * Returns the name of the class.
     */
    virtual std::string getClassName() const;
};

} // namespace pcs

#endif // PIECES_DISCONNECTED_EXCEPTION_H
