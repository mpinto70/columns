#include "State.h"

#include <utility>

namespace jogo {

State::State(const piece::Board& board,
      const score::ScoreBoard& score_board)
      : board_(board),
        score_board_(score_board),
        piece_(nullptr),
        piece_position_(nullptr),
        elimination_list_(),
        next_(nullptr) {
}

State::State(const piece::Board& board,
      const score::ScoreBoard& score_board,
      const piece::Piece& falling,
      const piece::PiecePosition& position,
      const piece::Piece& next)
      : board_(board),
        score_board_(score_board),
        piece_(new piece::Piece(falling)),
        piece_position_(new piece::PiecePosition(position)),
        elimination_list_(),
        next_(new piece::Piece(next)) {
}

State::State(const piece::Board& board,
      const score::ScoreBoard& score_board,
      const EliminationList& list,
      const piece::Piece& next)
      : board_(board),
        score_board_(score_board),
        piece_(nullptr),
        piece_position_(nullptr),
        elimination_list_(list),
        next_(new piece::Piece(next)) {
}

const piece::PiecePosition& State::piece_position() const {
    if (not has_piece_falling()) {
        throw std::logic_error("State::piece_position - there is no falling piece on the board");
    }
    return *piece_position_;
}

const piece::Piece& State::piece() const {
    if (not has_piece_falling()) {
        throw std::logic_error("State::piece - there is no falling piece on the board");
    }
    return *piece_;
}

const piece::Piece& State::next() const {
    if (not has_next()) {
        throw std::logic_error("State::next - there is no next piece");
    }
    return *next_;
}

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
