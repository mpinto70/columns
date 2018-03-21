#pragma once

#include "score/ScoreBoard.h"

namespace score {
bool operator==(const ScoreBoard& lhs, const ScoreBoard& rhs);
bool operator!=(const ScoreBoard& lhs, const ScoreBoard& rhs);
}
