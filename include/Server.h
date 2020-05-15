#pragma once

#include "common.h"
#include "DataStream.h"
#include "Broadcaster.h"
#include "WorkerSocket.h"

namespace MeyaS {
    class Server {
    public:
        Server() = default;
        MeyaS::uint startListening(MeyaS::uint peersDemanded, MeyaS::uint maxWaitTimeMilliseconds = 3000);
        const std::vector<DataStream*>& getPeers();
    private:
        std::vector<DataStream*> peers;
        Broadcaster* broadcaster{};
        ServerSocket* server{};
    };
}

