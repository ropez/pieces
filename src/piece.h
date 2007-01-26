#include "String"

#include <map>


class PropertyTable : public std::map<String, String> {};

const String EMPTY_STRING = "";

class Piece
{
public:

    Piece();
    virtual ~Piece();

    void setProperty(const String& property, const String& value);

    void setProperty(const String& property, int value);
    void setProperty(const String& property, double value);

    String getProperty(const String& property, const String& defval = EMPTY_STRING) const;

    int getPropertyAsInt(const String& property, int defval = 0) const;

    double getPropertyAsDouble(const String& property, double defval = 0.0) const;


private:
    PropertyTable m_properties;
};

