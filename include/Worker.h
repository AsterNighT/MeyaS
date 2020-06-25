#pragma once

#include "DataStream.h"

namespace MeyaS {
    // Worker connection of the server socket
    class Worker {
    public:
        Worker() = delete;
        ~Worker();
        explicit Worker(DataStream *p);

        //Get a DataStream to work with data sending and receiving.
        DataStream *getPeer();
        //Send a heartbeat to the client to check if connection is alive.
        bool checkStatus();
        //Inform the client that the server shall be shutdown.
        void shutdown();
    private:
        int maxWaitTime;
        DataStream *peer;
    };
}