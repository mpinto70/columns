#include "State.h"

#include <utility>

namespace state {

State::State(const piece::Board& board, const state::ScoreBoard& score_board)
      : board_(board),
        score_board_(score_board),
        piece_(nullptr),
        piece_position_(nullptr),
        elimination_list_(),
        next_(nullptr) {
}

State::State(const piece::Board& board,
      const state::ScoreBoard& score_board,
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
      const state::ScoreBoard& score_board,
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
}
