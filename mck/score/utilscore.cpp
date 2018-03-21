#include "utilscore.h"

namespace score {
bool operator==(const ScoreBoard& lhs, const ScoreBoard& rhs) {
    return lhs.record() == rhs.record()
           && lhs.score() == rhs.score();
}

bool operator!=(const ScoreBoard& lhs, const ScoreBoard& rhs) {
    return not(lhs == rhs);
}
}
