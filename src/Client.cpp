#include <ClientSocket.h>
#include <Timer.h>
#include <Broadcaster.h>
#include "Client.h"

bool MeyaS::Client::connectTo(MeyaS::Address *address) {
    auto *socket = new ClientSocket(address);
    if (!socket->connect()) return false;
    this->peer = new DataStream(socket);
    this->peer->setWaitTime(maxWaitTime);
    alive = true;
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

MeyaS::Client::Client() : maxWaitTime(50), peer(nullptr),alive(false) {
}

std::string MeyaS::Client::handleMessage() {
    auto message = peer->getLine();
    if (message.empty()) return "";
    if (message[0] == '#') { //command
        if (message == "#shutdown") {
            alive = false;
        }
        if (message == "#heart") {
            peer->sendLine("beat");
        }
    }
    return message;
}

MeyaS::Client::~Client() {
    delete peer;
}

bool MeyaS::Client::isAlive() const {
    return alive;
}
