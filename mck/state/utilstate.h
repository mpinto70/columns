#pragma once

#include "state/ScoreBoard.h"
#include "state/State.h"

namespace state {
bool operator==(const ScoreBoard& lhs, const ScoreBoard& rhs);
bool operator!=(const ScoreBoard& lhs, const ScoreBoard& rhs);
bool operator==(const State& lhs, const State& rhs);
bool operator!=(const State& lhs, const State& rhs);
namespace mck {
State create_state_(piece::SharedConstBoard board);
State create_state_(piece::SharedConstBoard board, SharedConstScoreBoard score_board);
} // namespace mck
} // namespace state
