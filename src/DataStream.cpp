#include <Timer.h>
#include "DataStream.h"

bool MeyaS::DataStream::send(const DataPack &data) {
    return socket->send(data);
}

MeyaS::DataPack *MeyaS::DataStream::recv(MeyaS::uint maxLength) {
    MeyaS::Timer t;
    t.start(maxWaitTime);
    while (!t.timeUp()) {
        auto ret = socket->recv(maxLength);
        if (ret != nullptr) return ret;
    }
    return nullptr;
}

MeyaS::DataStream::DataStream(MeyaS::DataSocket *socket) : socket(socket), maxWaitTime(3000), identifier(L"Meyas"),
                                                           cache(), cacheW() {}

MeyaS::DataStream::~DataStream() {
    delete socket;
    socket = nullptr;
}

bool MeyaS::DataStream::sendLine(std::string s, char delimiter) {
    s += delimiter;
    auto t = DataPack(s);
    return send(t);
}

std::string MeyaS::DataStream::getLine(char delimiter) {
    std::string s = cache;
    MeyaS::Timer t;
    t.start(maxWaitTime);
    while (!t.timeUp()) {
        auto ret = socket->recv(512);
        if (ret != nullptr) {
            auto retString = std::string(reinterpret_cast<const char *>(ret->data));
            delete ret;
            s += retString;
            auto pos = s.find(delimiter);
            if (pos != std::string::npos) { // Should be a full line
                cache = s.substr(pos + 1);
                s = s.substr(0, pos);
                return s;
            }
        }
    }
    return "";
}

void MeyaS::DataStream::setWaitTime(int time) {
    this->maxWaitTime = time;
}

bool MeyaS::DataStream::sendLineW(std::wstring s, wchar_t delimiter) {
    s += delimiter;
    auto t = DataPack(s);
    return send(t);
}

std::wstring MeyaS::DataStream::getLineW(wchar_t delimiter) {
    std::wstring s = cacheW;
    MeyaS::Timer t;
    t.start(maxWaitTime);
    while (!t.timeUp()) {
        auto ret = socket->recv(512);
        if (ret != nullptr) {
            auto retString = std::wstring(reinterpret_cast<const wchar_t *>(ret->data));
            delete ret;
            s += retString;
            auto pos = s.find(delimiter);
            if (pos != std::wstring::npos) { // Should be a full line
                cacheW = s.substr(pos + 1);
                s = s.substr(0, pos);
                return s;
            }
        }
    }
    return L"";
}
