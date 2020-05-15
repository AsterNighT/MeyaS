#include <iostream>
#include <Server.h>

#include "MeyaS.h"

int main() {
    MeyaS::initialize();
    auto soc = MeyaS::ServerSocket(MeyaS::Address::createAddress("127.0.0.1", "12448"));
    soc.bind();
    soc.listen();
    auto *worker = soc.accept();
    std::cout << worker->getPeerIP() << std::endl;
    auto p = worker->recv(2048);
    std::cout<< reinterpret_cast<const char *>(p.data)<<std::endl;
}

