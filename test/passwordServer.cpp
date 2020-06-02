#include <iostream>
#include <Server.h>

#include "MeyaS.h"

int main() {
    MeyaS::initialize();
    auto soc = MeyaS::Server();
    soc.startListening(1, 3000);
    auto peers = soc.getPeers();
    int peerCount=0;
    std::string passwd;
    MeyaS::Timer t;
    t.start(1000);
    while (1&&!t.timeUp()) {
        auto p = peers.at(0)->recv(2048);
        passwd+=std::string(reinterpret_cast<const char *>(p->data));
        if(passwd[passwd.length()-1]=='$'){
            if(passwd.substr(0,passwd.length()-1)=="password"){
                //success
            }else{
                //wrong password
                delete peers.at(0);
            }
        }
    }
}