#include <iostream>
#include <Server.h>

#include "MeyaS.h"

int main() {
    MeyaS::initialize();
    auto soc = MeyaS::Server();
    soc.startListening(1);
    auto peers = soc.getPeers();
    auto p = peers.at(0)->getPeer()->getLine();
    std::cout << p << std::endl;
}