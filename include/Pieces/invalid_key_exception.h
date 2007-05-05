
#ifndef PIECES_INVALID_KEY_EXCEPTION_H
#define PIECES_INVALID_KEY_EXCEPTION_H

#include "Pieces/Exception"


namespace pcs
{


/**
 * \class InvalidKeyException invalid_key_exception.h <Pieces/InvalidKeyException>
 * \brief Exceptionfor invalid key.
 *
 * This exception is thrown when a function is called with a key argument,
 * and a value for that key is not found in a data structure that stores
 * values by key.
 *
 * \author Robin Pedersen
 */
class InvalidKeyException : public Exception
{
public:

    /**
     * Default constructor.
     */
    InvalidKeyException();

    /**
     * Constructor that takes a message.
     */
    InvalidKeyException(const std::string& message);

    /**
     * Constructor that takes a function name and a message.
     */
    InvalidKeyException(const std::string& where, const std::string& message);

    /**
     * Returns the name of the class.
     */
    virtual std::string getClassName() const;
};

} // namespace pcs

#endif // PIECES_INVALID_KEY_EXCEPTION_H
