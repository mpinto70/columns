#include "utilgame.h"

#include "../mck/piece/utilpiece.h"
#include "../mck/score/utilscore.h"

namespace game {
bool operator==(const State& lhs, const State& rhs) {
    if (lhs.board() != rhs.board()) {
        return false;
    }
    if (lhs.score_board() != rhs.score_board()) {
        return false;
    }
    if (lhs.has_piece_falling() != rhs.has_piece_falling()) {
        return false;
    }
    if (lhs.has_piece_falling()) {
        if (lhs.piece() != rhs.piece()) {
            return false;
        }
        if (lhs.piece_position() != rhs.piece_position()) {
            return false;
        }
    }
    if (lhs.has_next() != rhs.has_next()) {
        return false;
    }
    if (lhs.has_next()) {
        if (lhs.next() != rhs.next()) {
            return false;
        }
    }
    if (lhs.elimination_list() != rhs.elimination_list()) {
        return false;
    }

    return true;
}

bool operator!=(const State& lhs, const State& rhs) {
    return not(lhs == rhs);
}
}
