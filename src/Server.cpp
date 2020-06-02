#include <Timer.h>
#include "Server.h"

const std::vector<MeyaS::DataStream *> &MeyaS::Server::getPeers() {
    return peers;
}

MeyaS::uint MeyaS::Server::startListening(MeyaS::uint peersDemanded, MeyaS::uint maxWaitTimeMilliseconds) {
    uint cnt = 0;
    broadcaster = new Broadcaster();
    server = new ServerSocket(DEFAULT_PORT);
    server->bind();
    server->listen();
    Timer t{};
    t.start(maxWaitTimeMilliseconds);
    DataPack data = DataPack((void *) "lo$", 4);
    while (!t.timeUp() && cnt < peersDemanded) {
        broadcaster->shout(data);
        auto *ptr = server->accept();
        if (ptr != nullptr) {
            peers.emplace_back(new DataStream(ptr));
            cnt++;
        }
    }
    return cnt;
}
