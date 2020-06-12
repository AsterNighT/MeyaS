#include <ClientSocket.h>
#include <Timer.h>
#include <Broadcaster.h>
#include "Client.h"

bool MeyaS::Client::connectTo(MeyaS::Address *address) {
    auto *socket = new ClientSocket(address);
    if (!socket->connect()) return false;
    this->peer = new DataStream(socket);
    this->peer->setWaitTime(maxWaitTime);
    return true;
}

std::vector<std::string> MeyaS::Client::probeServer() const {
    auto socket = Broadcaster();
    std::vector<std::string> servers;
    socket.listen();
    auto t = Timer();
    t.start(maxWaitTime + 3000);
    while (!t.timeUp()) {
        auto p = socket.accept();
        if (p.first != nullptr && p.first->length != 0) {
            servers.emplace_back(p.second);
        }
        delete p.first;
    }
    return servers;
}

MeyaS::DataStream *MeyaS::Client::getPeer() {
    return peer;
}

MeyaS::Client::Client() : maxWaitTime(50), peer(nullptr) {
}

std::string MeyaS::Client::handleMessage() {
    auto message = peer->getLine();
    cache += message;
    if (cache[cache.length() - 1] != '$') return "";//not ended yet;
    if (cache.empty()) return "";
    if (cache[0] == '#') { //command
        if (cache == "#shutdown$") {
            delete peer;
        }
        if (cache == "#heart$") {
            peer->sendLine("beat");
        }
    }
    auto tmp = cache.substr(0, cache.length() - 1); //delete $
    cache = "";
    return tmp;
}

MeyaS::Client::~Client() {
    delete peer;
}
