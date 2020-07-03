#pragma once
#define BROADCAST_RECV 1
#define BROADCAST_SEND 2

#include "Socket.h"
#include "Address.h"
#include "DataSocket.h"

namespace MeyaS {
    class Broadcaster : public Socket {
    public:
        Broadcaster();

        // Broadcast data
        bool shout(const DataPack &dataPack);

        bool listen();

        //Receive broadcast data
        std::pair<DataPack*, std::string> accept();

    private:
        uint type;
    };
}