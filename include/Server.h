#pragma once

#include "common.h"
#include "Broadcaster.h"
#include "ServerSocket.h"
#include "Worker.h"

namespace MeyaS {
    class Server {
    public:
        Server();
        MeyaS::uint startListening(MeyaS::uint peersDemanded);
        const std::vector<Worker*>& getPeers();
    private:
        int maxWaitTime;
        std::vector<Worker*> peers;
        Broadcaster* broadcaster;
        ServerSocket* server;
    };
}

