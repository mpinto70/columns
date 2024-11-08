#pragma once

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace mck {
std::string create_message(const std::string& file, int line);

template <typename T>
void check_comparison(const std::string& file,
      const int line,
      const std::vector<T>& ts) {
    const auto msg = create_message(file, line);
    EXPECT_NE(ts.size(), 0u) << msg;
    for (size_t i = 0; i < ts.size(); ++i) {
        for (size_t j = 0; j < ts.size(); ++j) {
            const auto msgij = msg + " " + std::to_string(i) + "/" + std::to_string(j);
            if (i == j) {
                EXPECT_EQ(ts[i], ts[j]) << msgij;
            } else {
                EXPECT_NE(ts[i], ts[j]) << msgij;
            }
        }
    }
}

template <typename T>
void check_comparison(const std::string& file,
      const int line,
      const std::vector<std::shared_ptr<const T>>& pts) {
    const auto msg = create_message(file, line);
    EXPECT_NE(pts.size(), 0u) << msg;
    for (size_t i = 0; i < pts.size(); ++i) {
        for (size_t j = 0; j < pts.size(); ++j) {
            const auto msgij = msg + " " + std::to_string(i) + "/" + std::to_string(j);
            if (i == j) {
                EXPECT_EQ(*pts[i], *pts[j]) << msgij;
            } else {
                EXPECT_NE(*pts[i], *pts[j]) << msgij;
            }
        }
    }
}

template <typename T>
void check_comparison(const std::string& file,
      const int line,
      const std::vector<std::shared_ptr<T>>& pts) {
    const auto msg = create_message(file, line);
    EXPECT_NE(pts.size(), 0u) << msg;
    for (size_t i = 0; i < pts.size(); ++i) {
        for (size_t j = 0; j < pts.size(); ++j) {
            const auto msgij = msg + " " + std::to_string(i) + "/" + std::to_string(j);
            if (i == j) {
                EXPECT_EQ(*pts[i], *pts[j]) << msgij;
            } else {
                EXPECT_NE(*pts[i], *pts[j]) << msgij;
            }
        }
    }
}

template <typename T>
void check_total_ordering(const std::string& file,
      const int line,
      const std::vector<T>& ts) {
    const auto msg = create_message(file, line);
    EXPECT_NE(ts.size(), 0u) << msg;
    for (size_t i = 0; i < ts.size(); ++i) {
        for (size_t j = 0; j < ts.size(); ++j) {
            const auto msgij = msg + " " + std::to_string(i) + "/" + std::to_string(j);
            if (i == j) {
                EXPECT_EQ(ts[i], ts[j]) << msgij;
            } else if (i < j) {
                EXPECT_LT(ts[i], ts[j]) << msgij;
            } else {
                EXPECT_LT(ts[j], ts[i]) << msgij;
            }
        }
    }
}

template <typename T>
void check_assignment(const std::string& file,
      const int line,
      const T& t1,
      const T& t2) {
    const auto msg = create_message(file, line);
    EXPECT_TRUE(not(t1 == t2)) << msg;

    T r1 = t1;
    T r2 = t2;

    EXPECT_EQ(t1, r1) << msg;
    EXPECT_EQ(t2, r2) << msg;

    EXPECT_NE(t1, r2) << msg;
    EXPECT_NE(t2, r1) << msg;

    r1 = t2;
    r2 = t1;

    EXPECT_EQ(t1, r2) << msg;
    EXPECT_EQ(t2, r1) << msg;

    EXPECT_NE(t1, r1) << msg;
    EXPECT_NE(t2, r2) << msg;
}
}
