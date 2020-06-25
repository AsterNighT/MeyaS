#include <iostream>
#include <Server.h>

#include "MeyaS.h"

int main() {
    //Initialize socket
    MeyaS::initialize();

    //Create server
    auto soc = MeyaS::Server();

    //Waiting for connection
    soc.startListening(1);

    //Receiving data
    auto peers = soc.getPeers();
    auto stream = peers.at(0)->getPeer();
    auto p = peers.at(0)->getPeer()->getLine();
    std::cout << p << std::endl;

    //Sending data
    stream->sendLine("Hello world 2");
}