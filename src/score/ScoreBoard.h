#pragma once

#include "score/Score.h"

namespace score {
/// Stores and processes score and record score
class ScoreBoard {
public:
    ScoreBoard(const Score& record = Score(0),
          const Score& score = Score(0));
    const Score& record() const { return record_; }
    const Score& score() const { return score_; }
    /** Increases score due to \p n tiles being destroyed.
     * @param n number of tiles that disappeared
     */
    void add(size_t n);
    void reset();

private:
    Score record_;
    Score score_;
};
}
