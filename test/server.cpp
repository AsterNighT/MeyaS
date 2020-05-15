#include <iostream>
#include <Server.h>

#include "MeyaS.h"

int main() {
    MeyaS::initialize();
    auto soc = MeyaS::Server();
    soc.startListening(1, 3000);
    auto peers = soc.getPeers();
    auto p = peers.at(0)->recv(2048);
    std::cout<< reinterpret_cast<const char *>(p->data)<<std::endl;
}