#include <Timer.h>
#include "Worker.h"

MeyaS::Worker::Worker(DataStream *p) : maxWaitTime(3000), cache(), peer(p) {

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
        cache += s;
        if (cache[cache.length() - 1] == '$') {
            if (cache == "#beat$") {
                cache = "";
                return true;
            } else {
                cache = "";
                return false;
            }
        }
    }
    return false;
}

void MeyaS::Worker::shutdown() {
    peer->sendLine("#shutdown");
}

MeyaS::Worker::~Worker() {
    delete peer;
}
