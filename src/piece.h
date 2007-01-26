
#ifndef PIECE_H
#define PIECE_H

#include "String"

#include <map>


class PropertyTable : public std::map<String, String> {};

class Piece
{
public:

    Piece();
    Piece(const String& str);
    virtual ~Piece();

    void setProperty(const String& property, const String& value);

    void setProperty(const String& property, int value);
    void setProperty(const String& property, double value);
    void setProperty(const String& property, const Piece& value);

    String getProperty(const String& property, const String& defval = EMPTY_STRING) const;

    int getPropertyAsInt(const String& property, int defval = 0) const;

    double getPropertyAsDouble(const String& property, double defval = 0.0) const;

    String toString() const;
    static Piece fromString(const String& str);

private:
    PropertyTable m_properties;
};

#endif // PIECE_H
