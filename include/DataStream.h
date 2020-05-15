#pragma once
#include "DataSocket.h"

namespace MeyaS {
    class DataStream {
    public:
        DataStream() = delete;
        virtual ~DataStream();
        explicit DataStream(DataSocket* socket);
        bool send(const DataPack &data);
        DataPack recv(uint maxLength);
    private:
        DataSocket* socket;
    };
}