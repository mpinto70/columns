#include "utilstate.h"

#include "../mck/piece/utilpiece.h"
#include "state/ScoreBoard.h"
#include "state/State.h"

namespace state {
bool operator==(const ScoreBoard& lhs, const ScoreBoard& rhs) {
    return lhs.record() == rhs.record() && lhs.score() == rhs.score();
}

bool operator!=(const ScoreBoard& lhs, const ScoreBoard& rhs) {
    return not(lhs == rhs);
}

bool operator==(const State& lhs, const State& rhs) {
    if (lhs.state() != rhs.state()) {
        return false;
    }
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
    if (lhs.has_next() && lhs.next() != rhs.next()) {
        return false;
    }
    if (lhs.has_elimination_list() != rhs.has_elimination_list()) {
        return false;
    }
    if (lhs.has_elimination_list() && lhs.elimination_list() != rhs.elimination_list()) {
        return false;
    }

    return true;
}

bool operator!=(const State& lhs, const State& rhs) {
    return not(lhs == rhs);
}

namespace mck {
State create_state_(piece::SharedConstBoard board, SharedConstScoreBoard score_board) {
    return State(board, score_board);
}

State create_state_(piece::SharedConstBoard board) {
    return State(board, std::make_shared<ScoreBoard>(Score{ 150 }, Score{ 20 }));
}
} // namespace mck
} // namespace state
