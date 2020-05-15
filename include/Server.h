#pragma once

#include "common.h"
#include "DataStream.h"
#include "Broadcaster.h"
#include "WorkerSocket.h"

namespace MeyaS {
    class Server {
    private:
        Server() = default;
        uint startListening(uint peersDemanded);
        const std::vector<DataStream*>& getPeers();
    private:
        std::vector<DataStream*> peers;
        Broadcaster* broadcaster{};
        ServerSocket* server{};
    };
}

