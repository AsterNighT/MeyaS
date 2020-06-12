#pragma once

#include "DataSocket.h"

namespace MeyaS {
    class DataStream {
    public:
        DataStream() = delete;

        virtual ~DataStream();

        explicit DataStream(DataSocket *socket);

        void setWaitTime(int time);

        bool send(const DataPack &data);

        DataPack *recv(uint maxLength);

        bool sendLine(std::string s, char delimiter = '$');

        std::string getLine(char delimiter = '$');

        std::string identifier;
    private:
        int maxWaitTime;
        DataSocket *socket;
    };
}