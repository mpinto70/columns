#pragma once

#include <cstdio>

namespace pontuacao {
/// Stores and processes score
class Score {
public:
    /**
     * @param total initial score
     */
    constexpr Score(size_t total = 0)
          : total_(total) {
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
