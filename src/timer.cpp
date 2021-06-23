#include "timer.h"

Timer::Timer(const unsigned long interval, bool immediately) : interval(interval), immediately(immediately) {}
Timer::Timer(const int ival, bool immediately) : immediately(immediately) {
    interval = (unsigned long)(ival);
}


bool Timer::tick(const unsigned long nowMillis) {
    if (prev == 0) {
        prev = nowMillis;
        return immediately;
    }

    auto diff = nowMillis - prev;
    if (diff >= interval) {
        prev = nowMillis;
        return true;
    }

    return false;
}




