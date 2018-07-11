#pragma once

#include <cstdio>

namespace state {
/// Stores and processes score
class Score {
public:
    constexpr explicit Score(size_t initial_score = 0)
          : total_(initial_score) {
    }

    constexpr size_t total() const { return total_; }
    /** Increases score due to \p n tiles being destroyed.
     * @param n number of tiles that disappeared
     */
    void add(size_t n);
    void reset() { total_ = 0; }

private:
    size_t total_; ///< score
};

constexpr bool operator==(const Score& lhs, const Score& rhs) {
    return lhs.total() == rhs.total();
}

constexpr bool operator!=(const Score& lhs, const Score& rhs) {
    return not(lhs == rhs);
}

constexpr bool operator<(const Score& lhs, const Score& rhs) {
    return lhs.total() < rhs.total();
}
}
