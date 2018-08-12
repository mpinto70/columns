#include "State.h"

#include <utility>

namespace state {

State::State(piece::SharedConstBoard board, SharedConstScoreBoard score_board)
      : state_(EState::CLEAN),
        board_(board),
        score_board_(score_board),
        next_(piece::NO_PIECE),
        piece_(piece::NO_PIECE),
        piece_position_(0),
        elimination_list_() {
}

bool State::has_next() const {
    return state_ != EState::CLEAN;
}

const piece::Piece& State::next() const {
    return next_;
}

bool State::has_piece_falling() const {
    return state_ == EState::FALLING;
}

const piece::Position& State::piece_position() const {
    return piece_position_;
}

const piece::Piece& State::piece() const {
    return piece_;
}

bool State::has_elimination_list() const {
    return state_ == EState::ELIMINATING;
}

const piece::Board::EliminationList& State::elimination_list() const {
    return elimination_list_;
}

void State::to_falling(const piece::Piece& next,
      const piece::Piece& falling,
      const piece::Position& position) {
    next_ = next;
    piece_ = falling;
    piece_position_ = position;
    state_ = EState::FALLING;
}

void State::still_falling(const piece::Piece& falling,
      const piece::Position& position) {
    piece_ = falling;
    piece_position_ = position;
    state_ = EState::FALLING;
}

void State::to_elimination() {
    elimination_list_ = board_->elimination_list();
    if (elimination_list_.empty())
        state_ = EState::ELIMINATED;
    else
        state_ = EState::ELIMINATING;
}
}
