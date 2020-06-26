
#include <Client.h>
#include <cstdio>
#include <io.h>
#include <fcntl.h>
#include "MeyaS.h"

int main() {
    _setmode(_fileno(stdout), 0x00020000);
    //Initialize socket
    MeyaS::initialize();

    //Create client
    auto client = MeyaS::Client();

    //Connect to server
    auto serverList = client.probeServer();
    while (serverList.empty()) serverList = client.probeServer();
    client.connectTo(MeyaS::Address::createAddress(serverList.at(0), DEFAULT_PORT));

    //Send data
    auto stream = client.getPeer();
    std::cout << serverList.at(0) << std::endl;
    auto p = MeyaS::DataPack(L"衬衫的价格是$");
    stream->send(p);

    //Receive data
    std::wstring s = client.handleMessage();
    while (s.empty()) s = client.handleMessage();
    std::wcout << s << std::endl;
}

