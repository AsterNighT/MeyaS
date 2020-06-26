#include <iostream>
#include <Server.h>
#include <cstdio>
#include <io.h>
#include "MeyaS.h"

int main() {
    _setmode(_fileno(stdout), 0x00020000);
    //Initialize socket
    MeyaS::initialize();

    //Create server
    auto soc = MeyaS::Server();

    //Waiting for connection
    soc.startListening(1);

    //Receiving data
    auto peers = soc.getPeers();
    auto stream = peers.at(0)->getPeer();
    auto p = stream->getLineW();
    std::wcout << p << std::endl;

    //Sending data
    stream->sendLineW(L"九磅十五便士");
}