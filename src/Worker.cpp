#include <Timer.h>
#include "Worker.h"

MeyaS::Worker::Worker(DataStream *p) : maxWaitTime(3000), peer(p) {

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
        return s == "#beat";
    }
    return false;
}

void MeyaS::Worker::shutdown() {
    peer->sendLine("#shutdown");
}

MeyaS::Worker::~Worker() {
    delete peer;
}
