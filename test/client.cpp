
#include <Client.h>

#include "MeyaS.h"
int main(){
    MeyaS::initialize();
    auto soc = MeyaS::ClientSocket(MeyaS::Address::createAddress("127.0.0.1","12448"));
    soc.connect();
    auto p = MeyaS::DataPack();
    p.data = reinterpret_cast<const byte *>("Hello world");
    p.length = 12;
    soc.send(p);
}

