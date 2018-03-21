#include "Wait.h"

#include <cstdlib>
#include <unistd.h>

namespace util {

Wait::Wait(const size_t time_ms)
      : wait_time_us_(time_ms * 1000),
        end_{ 0, 0 } {
    reset();
}

static constexpr suseconds_t MILLION = 1000 * 1000;
void Wait::reset() {
    gettimeofday(&end_, nullptr);
    end_.tv_usec += wait_time_us_;
    if (end_.tv_usec > MILLION) {
        const auto seconds_in_us = end_.tv_usec / MILLION;
        end_.tv_sec += seconds_in_us;
        end_.tv_usec %= MILLION;
    }
}

bool Wait::is_expired() const {
    timeval t;
    gettimeofday(&t, nullptr);
    if (t.tv_sec > end_.tv_sec) {
        return true;
    }
    if (t.tv_sec < end_.tv_sec) {
        return false;
    }
    return (t.tv_usec >= end_.tv_usec);
}

void Wait::wait() const {
    while (not is_expired()) {
        usleep(200);
    }
}
}
