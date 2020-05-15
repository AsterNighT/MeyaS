#include <ClientSocket.h>
#include <ServerSocket.h>
#include <Timer.h>
#include <Broadcaster.h>
#include "Client.h"

bool MeyaS::Client::connectTo(MeyaS::Address *address) {
    auto *socket = new ClientSocket(address);
    if (!socket->connect()) return false;
    this->peer = new DataStream(socket);
    return true;
}

std::vector<std::string> MeyaS::Client::probeServer() {
    auto socket = Broadcaster();
    std::vector<std::string> servers;
    socket.listen();
    auto t = Timer();
    t.start(1000);
    while (!t.timeUp()) {
        auto p = socket.accept();
        if (p.first.length != 0) {
            servers.emplace_back(p.second);
        }
    }
    return servers;
}

MeyaS::DataStream *MeyaS::Client::getPeer() {
    return peer;
}
