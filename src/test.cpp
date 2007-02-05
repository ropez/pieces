#include "Piece"
#include "List"

#include <iostream>
#include <sstream>

int main()
{
    Piece t;

    t.set("robin", "");
    t.set("angle", 2e23);
    t.set("documentation", "supercool stuff");

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


    std::cout << t.get<int>("Robin") << std::endl;
    std::cout << t.get<double>("angle") << std::endl;

    std::cout << t << std::endl;
    std::stringstream ss;
    ss << t;
    Piece p;
    ss >> p;
    p.set<Piece>("a-sub-piece", t);
    std::cout << p << std::endl;
    std::cout << p.get<String>("a-sub-piece") << std::endl;
}

