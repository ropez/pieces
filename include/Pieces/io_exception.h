#ifndef PIECES_IOEXCEPTION_H
#define PIECES_IOEXCEPTION_H

#include "Pieces/Exception"


namespace pcs
{


/**
 * \class IOException io_exception.h <Pieces/IOException>
 * \brief Input/output exception class.
 *
 * \author Thomas Bakken, Tord Heimdal
 */
class IOException : public Exception
{
public:

    /**
     * Default constructor.
     */
    IOException();

    /**
     * Constructor that takes a message.
     */
    IOException(const std::string& message);

    /**
     * Constructor that takes a function name and a message.
     */
    IOException(const std::string& where, const std::string& message);

    /**
     * Returns the name of the class.
     */
    virtual std::string getClassName() const;
};


} // namespace pcs

#endif // PIECES_IOEXCEPTION_H
