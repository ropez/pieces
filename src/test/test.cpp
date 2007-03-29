#include "Pieces/Application"
#include "Pieces/InetAddress"
#include <iostream>
#include <string>

using namespace Pieces;


int main(int argc, char** argv)
{
    Application application(argc, argv);

    std::cout << InetAddress::getHostByName("www.vg.no") << std::endl;
}

