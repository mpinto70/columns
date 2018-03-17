#include "util/Wait.h"

#include <gtest/gtest.h>

#include <sys/time.h>
#include <utility>

bool operator<(const timeval& lhs, const timeval& rhs) {
    if (lhs.tv_sec < rhs.tv_sec) {
        return true;
    }
    if (lhs.tv_sec > rhs.tv_sec) {
        return false;
    }
    return lhs.tv_usec < rhs.tv_usec;
}

static constexpr suseconds_t MILLION = 1000 * 1000;
timeval operator+(timeval lhs, const size_t mili) {
    lhs.tv_usec += mili * 1000;
    if (lhs.tv_usec > MILLION) {
        lhs.tv_sec += lhs.tv_usec / MILLION;
        lhs.tv_usec %= MILLION;
    }
    return lhs;
}

double operator-(const timeval& lhs, const timeval& rhs) {
    const int dsec = (lhs.tv_sec - rhs.tv_sec) * (int) MILLION;
    const int dusec = lhs.tv_usec - rhs.tv_usec;
    return (dsec + dusec) / 1000.0;
}

namespace util {
namespace tst {

namespace {
void print(const std::string& id, const timeval& val) {
    printf("%15s = %8ld / %8ld\n", id.c_str(), val.tv_sec, val.tv_usec);
}

void print(const int line,
      const size_t mili,
      const timeval& depois,
      const timeval& fim) {
    printf("\n");
    printf("from line = %d\n", line);
    printf("wait length = %zu\n", mili);
    print("after", depois);
    print("end", fim);
    printf("difference = %lf\n", fim - depois);
}

void check_wait(const size_t mili) {
    using namespace std::rel_ops;
    timeval after;

    Wait wait(mili);
    auto end = wait.end();
    for (size_t i = 0; i < 10; ++i) {
        EXPECT_FALSE(wait.is_expired()) << mili;
    }
    wait.wait();
    EXPECT_TRUE(wait.is_expired()) << mili;
    gettimeofday(&after, nullptr);
    EXPECT_TRUE(end <= after) << mili;
    if (end > after) {
        print(__LINE__, mili, after, end);
    }

    wait.reset();
    end = wait.end();
    for (size_t i = 0; i < 10; ++i) {
        EXPECT_FALSE(wait.is_expired()) << mili;
    }
    wait.wait();
    EXPECT_TRUE(wait.is_expired()) << mili;
    gettimeofday(&after, nullptr);

    EXPECT_TRUE(end <= after) << mili;
    if (end > after) {
        print(__LINE__, mili, after, end);
    }
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
    using namespace std::rel_ops;
    timeval before;

    gettimeofday(&before, nullptr);
    Wait wait(mili);
    auto end = before + mili;
    EXPECT_TRUE(before < wait.end()) << mili;
    EXPECT_TRUE(end <= wait.end()) << mili;

    gettimeofday(&before, nullptr);
    wait.reset();
    end = before + mili;
    EXPECT_TRUE(before < wait.end()) << mili;
    EXPECT_TRUE(end <= wait.end()) << mili;
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
