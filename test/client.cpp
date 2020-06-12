
#include <Client.h>

#include "MeyaS.h"
int main(){
    MeyaS::initialize();
    auto client = MeyaS::Client();
    auto serverList = client.probeServer();
    while(serverList.empty()) serverList = client.probeServer();
    client.connectTo(MeyaS::Address::createAddress(serverList.at(0),DEFAULT_PORT));
    auto stream = client.getPeer();
    std::cout<<serverList.at(0)<<std::endl;
    auto p = MeyaS::DataPack("Hello world$");
    stream->send(p);
}

