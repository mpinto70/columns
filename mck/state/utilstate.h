#pragma once

#include "state/ScoreBoard.h"
#include "state/State.h"

namespace state {
bool operator==(const ScoreBoard& lhs, const ScoreBoard& rhs);
bool operator!=(const ScoreBoard& lhs, const ScoreBoard& rhs);
bool operator==(const State& lhs, const State& rhs);
bool operator!=(const State& lhs, const State& rhs);

State create_state(const piece::Board& board);
}
