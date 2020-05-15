#include "Exception.h"
#include "WorkerSocket.h"

MeyaS::WorkerSocket::WorkerSocket(SOCKET sockfd, std::string ip) {
    this->sockfd = sockfd;
    this->ip = std::move(ip);
}

const std::string &MeyaS::WorkerSocket::getPeerIP() {
    return ip;
}