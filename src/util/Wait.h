#pragma once

#include <cstdio>
#include <sys/time.h>

namespace util {
/// Responsible for assuring a certain time is elapsed.
class Wait {
public:
    /// @param time_ns minimum time in milliseconds to wait
    explicit Wait(size_t time_ms);
    ~Wait() = default;

    void reset();
    bool is_expired() const;
    void wait() const;
    const timeval& end() const { return end_; }

private:
    size_t wait_time_us_; ///< time to wait in microseconds
    timeval end_;         ///< end time
};
}
