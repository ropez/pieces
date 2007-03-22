
#include "Pieces/InetAddress"
#include <iostream>
#include <string>

#if defined WIN32
#include <winsock2.h>
#endif

using namespace Pieces;


int main()
{

#if defined WIN32
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD( 2, 2 );

    err = WSAStartup( wVersionRequested, &wsaData );
#endif

    std::cout << InetAddress::getHostByName("www.vg.no") << std::endl;

#if defined WIN32
    WSACleanup();
#endif

    //std::string str;
    //std::cin >> str;
}

