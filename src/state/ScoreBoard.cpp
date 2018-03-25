#include "ScoreBoard.h"

#include <stdexcept>
#include <string>

namespace state {

ScoreBoard::ScoreBoard(const Score& record,
      const Score& score)
      : record_(record),
        score_(score) {
    if (record_ < score_)
        throw std::invalid_argument("ScoreBoard - record ("
                                    + std::to_string(record.total())
                                    + ") is less than the score ("
                                    + std::to_string(score.total())
                                    + ")");
}

void ScoreBoard::add(const size_t n) {
    score_.add(n);
    if (record_ < score_) {
        record_ = score_;
    }
}

void ScoreBoard::reset() {
    score_.reset();
}
}
