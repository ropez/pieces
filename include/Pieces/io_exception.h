#ifndef PIECES_IOEXCEPTION_H
#define PIECES_IOEXCEPTION_H

#include "Pieces/Exception"


namespace pcs
{


/**
 * \class IOException
 * \brief Input/output exception class
 *
 * \author Thomas and Tord
 */
class IOException : public Exception
{
public:
    IOException();
    IOException(const std::string& message);
    IOException(const std::string& where, const std::string& message);

    virtual std::string getClassName() const;
};


} // namespace pcs

#endif // PIECES_IOEXCEPTION_H
