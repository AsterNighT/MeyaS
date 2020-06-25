#pragma once
#include "DataStream.h"
#include "Address.h"
#define DEFAULT_SERVER_PROBE_PORT "12449"
namespace MeyaS {
    class Client {
    public:
        Client();
        ~Client();
        bool connectTo(Address* address);
        std::vector<std::string> probeServer() const;
        std::string handleMessage();
        DataStream* getPeer();
    private:
        int maxWaitTime;
        DataStream* peer;
    };
}