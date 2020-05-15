#include "DataStream.h"

bool MeyaS::DataStream::send(const DataPack &data) {
    return socket->send(data);
}

MeyaS::DataPack MeyaS::DataStream::recv(MeyaS::uint maxLength) {
    return socket->recv(maxLength);
}

MeyaS::DataStream::DataStream(MeyaS::DataSocket *socket):socket(socket) {}

MeyaS::DataStream::~DataStream() {
    delete socket;
    socket = nullptr;
}
