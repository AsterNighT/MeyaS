#include <Timer.h>
#include "Server.h"

const std::vector<MeyaS::Worker *> &MeyaS::Server::getPeers() {
    return peers;
}

MeyaS::uint MeyaS::Server::startListening(MeyaS::uint peersDemanded) {
    uint cnt = 0;
    seats = peersDemanded;
    if(seats <= 0) return 0;
    peers.clear();
    broadcaster = new Broadcaster();
    server = new ServerSocket(DEFAULT_PORT);
    server->bind();
    server->listen();
    Timer t{};
    t.start(maxWaitTime);
    DataPack data = DataPack((void *) "lo$", 4);
    while (!t.timeUp() && cnt < peersDemanded) {
        broadcaster->shout(data);
        auto *ptr = server->accept();
        if (ptr != nullptr) {
            peers.emplace_back(new Worker(new DataStream(ptr)));
            cnt++;
        }
    }
    return cnt;
}

MeyaS::Server::Server(): maxWaitTime(30), broadcaster(nullptr), server(nullptr), seats(0) {

}

bool MeyaS::Server::accept() {
    if(seats <= 0) return false;
    if(broadcaster== nullptr||server== nullptr) return false;
    DataPack data = DataPack((void *) "lo$", 4);
    broadcaster->shout(data);
    auto *ptr = server->accept();
    if (ptr != nullptr) {
        peers.emplace_back(new Worker(new DataStream(ptr)));
        seats--;
        return true;
    }
    return false;
}

bool MeyaS::Server::stopListening() {
    delete broadcaster; broadcaster = nullptr;
    delete server; server = nullptr;
    seats = 0;
    return true;
}

bool MeyaS::Server::isFullyConnected() const {
    return seats <= 0;
}
