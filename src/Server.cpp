#include <Timer.h>
#include "Server.h"

const std::vector<MeyaS::Worker *> &MeyaS::Server::getPeers() {
    return peers;
}

MeyaS::uint MeyaS::Server::startListening(MeyaS::uint peersDemanded) {
    uint cnt = 0;
    broadcaster = new Broadcaster();
    server = new ServerSocket(DEFAULT_PORT);
    server->bind();
    server->listen();
    Timer t{};
    t.start(maxWaitTime*100);
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

MeyaS::Server::Server():maxWaitTime(3000),broadcaster(nullptr),server(nullptr) {

}
