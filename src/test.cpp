#include "Piece"
#include "List"

#include <iostream>
#include <sstream>

int main()
{
    Piece t;

    t.set("robin", 10).set("angle", 2e23).set("documentation", "supercool stuff");

    List l;
    l.append("a");
    l.append("b");
    l.append("c");
    l.append("joakim simonsson");

    std::cout << l << std::endl;
    std::stringstream s;
    s << l;
    List m;
    s >> m;
    std::cout << m << std::endl;
    std::cout << m.at(3) << std::endl;


    std::cout << t.get<int>("robin") << std::endl;
    std::cout << t.get<double>("angle") << std::endl;

    std::cout << t << std::endl;
    std::stringstream ss;
    ss << t;
    Piece p;
    ss >> p;
    p.set<Piece>("a-sub-piece", t);
    p.set("a-sub-list", l);
    std::cout << p << std::endl;
    std::cout << p.get<String>("a-sub-piece") << std::endl;
    std::cout << p.get<List>("a-sub-list").at(3) << std::endl;
}

