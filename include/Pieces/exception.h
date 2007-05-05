#ifndef PIECES_EXCEPTION_H
#define PIECES_EXCEPTION_H

#include <string>
#include <ostream>


namespace pcs
{


/**
 * \class Exception exception.h <Pieces/Exception>
 * \brief Base exception class
 *
 * This is a base class for all exceptions used in Pieces.
 *
 * All exceptions in Pieces should be catched as \em const \em reference. This
 * makes it possible to handle all exceptions with a reference to this generic
 * type.
 *
 * \author Robin Pedersen
 */
class Exception
{
public:

    /**
     * Create an exception without a message.
     */
    Exception();

    /**
     * Create an exception with the given \a message.
     */
    Exception(const std::string& message);

    /**
     * Create an exception thrown from a given function \a where,
     * with a given \a message.
     */
    Exception(const std::string& where, const std::string& message);

    /**
     * Destructor.
     */
    virtual ~Exception();

    /**
     * Reimplement in all subclasses to return the name of the class.
     *
     * This is used to get the cirrect exception type when writing to
     * an ostream (like a pcs::DebugStream).
     */
    virtual std::string getClassName() const;

    /**
     * Returns the function where the exception was thrown from, if any.
     */
    std::string getWhere() const;

    /**
     * Returns the exception message, if any.
     */
    std::string getMessage() const;

private:

    std::string m_where;
    std::string m_message;
};

/**
 * Writes the exception type and message to the output stream.
 *
 * \relates Exception
 */
std::ostream& operator<<(std::ostream& os, const Exception& e);

} // namespace pcs

#endif // PIECES_EXCEPTION_H
