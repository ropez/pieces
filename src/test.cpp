#include "Piece"
#include "List"

#include <iostream>
#include <sstream>

int main()
{
    Piece t;

    t.setProperty("robin", "");
    t.setProperty("angle", 2e23);
    t.setProperty("documentation", "supercool stuff");

    List l;
    l.append("a");
    l.append("b");
    l.append("c");
    l.append("joakim");

    std::cout << l << std::endl;
    std::stringstream s;
    s << l;
    List m;
    s >> m;
    std::cout << m << std::endl;
    std::cout << m.at(3) << std::endl;


//     std::cout << t.getPropertyAsInt("Robin", 12) << std::endl;
    std::cout << t.getProperty("angle") << std::endl;

    std::cout << t << std::endl;
    std::stringstream ss;
    ss << t;
    Piece p;
    ss >> p;
    p.setProperty("a-sub-piece", t);
    std::cout << p << std::endl;
    std::cout << p.getPropertyAsPiece("sub-piece").getProperty("angle") << std::endl;
}

