#pragma once

#include <chrono>

namespace util {
/// Responsible for assuring a certain time is elapsed.
class Wait {
public:
    using Clock = std::chrono::high_resolution_clock;
    /// @param wait_time the size of the wait
    explicit Wait(Clock::duration wait_time);
    ~Wait() = default;

    void reset();
    void wait() const;

    Clock::time_point end() const { return end_; }

private:
    Clock::duration wait_time_; ///< time to wait in microseconds
    Clock::time_point end_;     ///< end time
};
} // namespace util
