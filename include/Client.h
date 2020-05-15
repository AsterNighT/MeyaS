#pragma once
#include "DataStream.h"
#include "Address.h"
#define DEFAULT_SERVER_PROBE_PORT "12449"
namespace MeyaS {
    class Client {
    public:
        Client() = default;
        bool connectTo(Address* address);
        static std::vector<std::string> probeServer();
        DataStream* getPeer();
    private:
        DataStream* peer;
    };
}