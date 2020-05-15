#include <Exception.h>
#include "DataSocket.h"

MeyaS::DataPack MeyaS::DataSocket::recv(uint maxLength) {
    char recvbuf[maxLength];
    int iResult;
    iResult = ::recv(sockfd, recvbuf, maxLength, 0);
    if (iResult == SOCKET_ERROR) {
        auto err = WSAGetLastError();
        if (err != WSAEWOULDBLOCK) {
            std::cerr << "recv failed: " << WSAGetLastError() << std::endl;
            closesocket(sockfd);
            sockfd = INVALID_SOCKET;
            WSACleanup();
            DebugException("Recv failed");
        }
        return {};
    }
    auto ret = DataPack(recvbuf, iResult);
    ret.type = 0;
    return ret;
}

bool MeyaS::DataSocket::send(const DataPack &dataPack) {
    int iResult = ::send(sockfd, reinterpret_cast<const char *>(dataPack.data), dataPack.length, 0);
    if (iResult == SOCKET_ERROR) {
        auto err = WSAGetLastError();
        if (err != WSAEWOULDBLOCK) {
            std::cerr << "Send failed: " << WSAGetLastError() << std::endl;
            closesocket(sockfd);
            sockfd = INVALID_SOCKET;
            WSACleanup();
            DebugException("Send failed");
        }
        return false;
    }
    return true;
}

MeyaS::DataPack::DataPack() : data(nullptr), length(0), type(0) {}

MeyaS::DataPack::DataPack(void *data, MeyaS::uint length) : length(length), type(0) {
    this->data = new byte(length);
    memcpy((void *) this->data, data, length);
}

MeyaS::DataPack::~DataPack() {
    delete this->data;
    this->data = nullptr;
}
