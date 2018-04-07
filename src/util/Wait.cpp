#include "Wait.h"

#include <thread>

namespace util {

Wait::Wait(Clock::duration wait_time)
      : wait_time_(wait_time),
        end_{ Clock::now() + wait_time } {
}

void Wait::reset() {
    end_ = Clock::now() + wait_time_;
}

bool Wait::is_expired() const {
    return Clock::now() > end_;
}

void Wait::wait() const {
    std::this_thread::sleep_until(end_);
}
}
