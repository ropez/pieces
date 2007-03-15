#ifndef PIECES_EXCEPTION_H
#define PIECES_EXCEPTION_H

#include <string>
#include <ostream>


namespace Pieces
{


/**
 * \class Exception
 * \brief Base exception class
 *
 * This is a base class for all exceptions used in Pieces.
 *
 * \author Robin Pedersen
 */
class Exception
{
public:
    Exception();
    Exception(const std::string& message);
    Exception(const std::string& where, const std::string& message);
    virtual ~Exception();

    /**
     * Reimplement in all subclasses to return the name of the class.
     */
    virtual std::string getClassName() const;

    std::string getWhere() const;
    std::string getMessage() const;

private:

    std::string m_where;
    std::string m_message;
};

std::ostream& operator<<(std::ostream& os, const Exception& e);

} // namespace Pieces

#endif // PIECES_EXCEPTION_H
