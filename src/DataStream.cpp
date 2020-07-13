#include <Timer.h>
#include "DataStream.h"

int MeyaS::DataStream::send(const DataPack &data) {
    return socket->send(data);
}

MeyaS::DataPack *MeyaS::DataStream::recv(MeyaS::uint maxLength) {
    MeyaS::Timer t;
    t.start(maxWaitTime);
    do {
        auto ret = socket->recv(maxLength);
        if (ret != nullptr) return ret;
    } while (!t.timeUp());
    return nullptr;
}

MeyaS::DataStream::DataStream(MeyaS::DataSocket *socket) : socket(socket), maxWaitTime(5), identifier(CPMeyaS("Meyas")),
                                                           cache(){}

MeyaS::DataStream::~DataStream() {
    delete socket;
    socket = nullptr;
}

int MeyaS::DataStream::sendLine(String_MeyaS s, Char_MeyaS delimiter) {
    s += delimiter;
    auto t = DataPack(s);
    return send(t);
}

String_MeyaS MeyaS::DataStream::getLine(Char_MeyaS delimiter) {
    String_MeyaS s;
    auto pos = cache.find(delimiter);
    if (pos != String_MeyaS::npos) { // Should be a full line
        s = cache.substr(0, pos);
        cache = cache.substr(pos + 1);
        return s;
    }
    MeyaS::Timer t;
    t.start(maxWaitTime);
    do {
        auto ret = socket->recv(512);
        if (ret != nullptr) {
            auto retString = String_MeyaS(reinterpret_cast<const Char_MeyaS *>(ret->data));
            cache += retString;
            MeyaS::uint totalLength = retString.length() + 1;
            while (totalLength < ret->length / sizeof(Char_MeyaS)) { // More data to be retrieved
                retString = String_MeyaS(reinterpret_cast<const Char_MeyaS *>(ret->data) + totalLength);
                cache += retString;
                totalLength += retString.length() + 1;
            }
            delete ret;
            pos = cache.find(delimiter);
            if (pos != String_MeyaS::npos) { // Should be a full line
                s = cache.substr(0, pos);
                cache = cache.substr(pos + 1);
                return s;
            }
        }
    } while (!t.timeUp());
    return CPMeyaS("");
}

void MeyaS::DataStream::setWaitTime(int time) {
    this->maxWaitTime = time;
}
