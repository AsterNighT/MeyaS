#include <Timer.h>
#include "Worker.h"

MeyaS::Worker::Worker(DataStream *p) : maxWaitTime(3000), peer(p),alive(true) {

}

MeyaS::DataStream *MeyaS::Worker::getPeer() {
    return peer;
}

bool MeyaS::Worker::checkStatus() {
    peer->sendLine("#heart");
    MeyaS::Timer t;
    t.start(maxWaitTime);
    while (!t.timeUp()) {
        auto s = peer->getLine();
        if (s.empty()) continue;
        if(s == "#beat"){
            return true;
        }else{
            alive = false;
            return false;
        }
    }
    alive = false;
    return false;
}

void MeyaS::Worker::shutdown() {
    peer->sendLine("#shutdown");
    alive = false;
}

MeyaS::Worker::~Worker() {
    delete peer;
}

bool MeyaS::Worker::isAlive() const {
    return alive;
}
