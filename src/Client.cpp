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
    do {
        auto p = socket.accept();
        if (p.first != nullptr && p.first->length != 0) {
            servers.emplace_back(p.second);
        }
        delete p.first;
    } while (!t.timeUp());
    return servers;
}

MeyaS::DataStream *MeyaS::Client::getPeer() {
    return peer;
}

MeyaS::Client::Client() : maxWaitTime(1), peer(nullptr), alive(false) {
}

String_MeyaS MeyaS::Client::handleMessage() {
    auto message = peer->getLine();
    if (message.empty()) return CPMeyaS("");
    if (message[0] == CPMeyaS('#')) { //command
        if (message == CPMeyaS("#shutdown")) {
            alive = false;
        }
        if (message == CPMeyaS("#heart")) {
            peer->sendLine(CPMeyaS("#beat"));
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
