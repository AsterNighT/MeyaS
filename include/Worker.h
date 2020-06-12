#pragma once

#include "DataStream.h"

namespace MeyaS {
    class Worker {
    public:
        Worker() = delete;
        ~Worker();
        explicit Worker(DataStream *p);

        DataStream *getPeer();
        bool checkStatus();
        void shutdown();
    private:
        std::string cache;
        int maxWaitTime;
        DataStream *peer;
    };
}