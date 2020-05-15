#include "Exception.h"
#include "ClientSocket.h"

MeyaS::ClientSocket::ClientSocket(Address *serverAddress) : serverAddress(serverAddress) {
    addrinfo *result = nullptr, hints{};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    int iResult = getaddrinfo(this->serverAddress->getIP().c_str(), this->serverAddress->getPort().c_str(), &hints,
                              &result);
    if (iResult != 0) {
        std::cerr << "Getaddrinfo failed: " << iResult << std::endl;
        WSACleanup();
        DebugException("Getaddrinfo failed");
    }
    initialize(result);
    setBlocking(false);
}

bool MeyaS::ClientSocket::connect() {
    addrinfo *ptr = addrInfo;
    int iResult = SOCKET_ERROR;
    while (ptr != nullptr && iResult == SOCKET_ERROR) {
        iResult = ::connect(sockfd, ptr->ai_addr, (int) ptr->ai_addrlen);
    }
    if (iResult == SOCKET_ERROR) {
        std::cerr << "Unable to connect to server!" << std::endl;
        closesocket(sockfd);
        freeaddrinfo(addrInfo);
        sockfd = INVALID_SOCKET;
        addrInfo = nullptr;
        WSACleanup();
        DebugException("Unable to connect to server");
        return false;
    }
    freeaddrinfo(addrInfo);
    addrInfo = nullptr;
    return true;
}
