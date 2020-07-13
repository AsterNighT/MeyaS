#include <Timer.h>
#include "Worker.h"

MeyaS::Worker::Worker(DataStream *p) : maxWaitTime(3000), peer(p), alive(true) {
}

MeyaS::DataStream *MeyaS::Worker::getPeer() {
    return peer;
}

String_MeyaS MeyaS::Worker::checkStatus() {
    auto ret = peer->sendLine(CPMeyaS("#heart"));
    if (ret != 0) {
        alive = false;
        return CPMeyaS("");
    }
    MeyaS::Timer t;
    t.start(maxWaitTime);
    do {
        auto s = peer->getLine();
        if (s.empty()) continue;
        return s;
    } while (!t.timeUp());
    alive = false;
    return CPMeyaS("");
}

void MeyaS::Worker::shutdown() {
    peer->sendLine(CPMeyaS("#shutdown"));
    alive = false;
}

MeyaS::Worker::~Worker() {
    delete peer;
}

bool MeyaS::Worker::isAlive() const {
    return alive;
}
