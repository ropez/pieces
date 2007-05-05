#ifndef PIECES_TIMEOUT_EXCEPTION_H
#define PIECES_TIMEOUT_EXCEPTION_H

#include "Pieces/IOException"


namespace pcs
{


/**
 * \class TimeoutException timeout_exception.h <Pieces/TimeoutException>
 * \brief Input/output timeout exception class.
 *
 * \author Thomas Bakken, Tord Heimdal
 */
class TimeoutException : public IOException
{
public:

    /**
     * Default constructor.
     */
    TimeoutException();

    /**
     * Constructor that takes a message.
     */
    TimeoutException(const std::string& message);

    /**
     * Constructor that takes a function name and a message.
     */
    TimeoutException(const std::string& where, const std::string& message);

    /**
     * Returns the name of the class.
     */
    virtual std::string getClassName() const;
};


} // namespace pcs

#endif // PIECES_TIMEOUT_EXCEPTION_H
