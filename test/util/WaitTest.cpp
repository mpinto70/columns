#include "util/Wait.h"

#include <gtest/gtest.h>

#include <chrono>
#include <utility>

namespace util {
namespace tst {

namespace {
void check_wait(const size_t mili) {
    using namespace std::rel_ops;
    Wait::Clock::time_point after;

    Wait wait(std::chrono::milliseconds{ mili });
    Wait::Clock::time_point end = wait.end();
    wait.wait();
    after = Wait::Clock::now();
    EXPECT_LE(end, after) << mili;

    wait.reset();
    end = wait.end();
    wait.wait();
    after = Wait::Clock::now();
    EXPECT_LE(end, after) << mili;
}
}

TEST(WaitTest, wait) {
    for (size_t i = 0; i < 10; ++i) {
        check_wait(1);
        check_wait(10);
        check_wait(20);
        check_wait(30);
    }
}

namespace {
void check_end(const size_t mili) {
    Wait::Clock::time_point before = Wait::Clock::now();
    Wait wait(std::chrono::milliseconds{ mili });
    Wait::Clock::time_point end = before + std::chrono::milliseconds{ mili };
    EXPECT_LT(before, wait.end()) << mili;
    EXPECT_LE(end, wait.end()) << mili;

    before = Wait::Clock::now();
    wait.reset();
    end = before + std::chrono::milliseconds{ mili };
    EXPECT_LT(before, wait.end()) << mili;
    EXPECT_LE(end, wait.end()) << mili;
}
}

TEST(WaitTest, end) {
    for (size_t i = 0; i < 1000; ++i) {
        check_end(1);
        check_end(10);
        check_end(20);
        check_end(30);
    }
}
}
}
