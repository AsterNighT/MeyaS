#include <Timer.h>
#include "Worker.h"

MeyaS::Worker::Worker(DataStream *p) : maxWaitTime(3000), peer(p), alive(true) {
}

MeyaS::DataStream *MeyaS::Worker::getPeer() {
    return peer;
}

bool MeyaS::Worker::checkStatus() {
    auto ret = peer->sendLineW(L"#heart");
    if (ret != 0) {
        alive = false;
        return false;
    }
    MeyaS::Timer t;
    t.start(maxWaitTime);
    while (!t.timeUp()) {
        auto s = peer->getLineW();
        if (s.empty()) continue;
        if (peer->cacheW.length() != 0) {
            std::cout << peer->cacheW.length() << std::endl;
        }
        if (s == L"#beat") {
            return true;
        } else {
            alive = false;
            return false;
        }
    }
    alive = false;
    return false;
}

void MeyaS::Worker::shutdown() {
    peer->sendLineW(L"#shutdown");
    alive = false;
}

MeyaS::Worker::~Worker() {
    delete peer;
}

bool MeyaS::Worker::isAlive() const {
    return alive;
}
