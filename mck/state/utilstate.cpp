#include "utilstate.h"

#include "../mck/piece/utilpiece.h"

#include "state/ScoreBoard.h"
#include "state/State.h"

namespace state {
bool operator==(const ScoreBoard& lhs, const ScoreBoard& rhs) {
    return lhs.record() == rhs.record()
           && lhs.score() == rhs.score();
}

bool operator!=(const ScoreBoard& lhs, const ScoreBoard& rhs) {
    return not(lhs == rhs);
}

bool operator==(const State& lhs, const State& rhs) {
    if (*lhs.board() != *rhs.board()) {
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
StatePtr create_state(piece::SharedConstBoard board) {
    return create_state(board, ScoreBoard{ Score{ 150 }, Score{ 20 } });
}

StatePtr create_state(piece::SharedConstBoard board, const state::ScoreBoard& score_board) {
    return std::make_unique<State>(board, score_board);
}

StatePtr create_state(piece::SharedConstBoard board,
      const state::ScoreBoard& score_board,
      const piece::Piece& next,
      const piece::Piece& falling,
      const piece::PiecePosition& position) {
    return std::make_unique<StateFalling>(board, score_board, next, falling, position);
}

StatePtr create_state(piece::SharedConstBoard board,
      const state::ScoreBoard& score_board,
      const piece::Piece& next,
      const piece::Board::EliminationList& elimination) {
    return std::make_unique<StateElimination>(board, score_board, next, elimination);
}
}
}
