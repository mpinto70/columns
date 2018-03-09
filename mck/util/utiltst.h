#pragma once

#include "gtest/gtest.h"

#include <string>
#include <utility>
#include <vector>

namespace mck {
std::string montaMensagem(const std::string& file,
      int line);

template <typename T>
void confereComparacao(const std::string& file,
      const int line,
      const std::vector<T>& ts) {
    const auto msg = montaMensagem(file, line);
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
void confereAtribuicaoSwap(const std::string& file,
      const int line,
      const T& t1,
      const T& t2) {
    const auto msg = montaMensagem(file, line);
    EXPECT_TRUE(not(t1 == t2)) << msg;

    auto r1 = t1;
    auto r2 = t2;

    EXPECT_EQ(t1, r1) << msg;
    EXPECT_EQ(t2, r2) << msg;

    EXPECT_NE(t1, r2) << msg;
    EXPECT_NE(t2, r1) << msg;

    r1.swap(r2);

    EXPECT_EQ(t1, r2) << msg;
    EXPECT_EQ(t2, r1) << msg;

    EXPECT_NE(t1, r1) << msg;
    EXPECT_NE(t2, r2) << msg;
}
}
