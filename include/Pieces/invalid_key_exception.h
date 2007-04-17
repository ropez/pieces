
#ifndef PIECES_INVALID_KEY_EXCEPTION_H
#define PIECES_INVALID_KEY_EXCEPTION_H

#include "Pieces/Exception"


namespace pcs
{


class InvalidKeyException : public Exception
{
public:
    InvalidKeyException();
    InvalidKeyException(const std::string& message);
    InvalidKeyException(const std::string& where, const std::string& message);

    virtual std::string getClassName() const;
};

} // namespace pcs

#endif // PIECES_INVALID_KEY_EXCEPTION_H
