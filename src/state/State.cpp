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
    if (not has_next()) {
        throw std::logic_error("State::next - no next");
    }
    return next_;
}

bool State::has_piece_falling() const {
    return state_ == EState::FALLING;
}

const piece::Position& State::piece_position() const {
    if (not has_piece_falling()) {
        throw std::logic_error("State::piece_position - no piece falling");
    }
    return piece_position_;
}

const piece::Piece& State::piece() const {
    if (not has_piece_falling()) {
        throw std::logic_error("State::piece - no piece falling");
    }
    return piece_;
}

bool State::has_elimination_list() const {
    return state_ == EState::ELIMINATING;
}

const piece::Board::EliminationList& State::elimination_list() const {
    if (not has_elimination_list()) {
        throw std::logic_error("State::elimination_list - no elimination list");
    }
    return elimination_list_;
}

void State::to_clean() {
    state_ = EState::CLEAN;
}

void State::to_falling(const piece::Piece& next,
      const piece::Piece& falling,
      const piece::Position& position) {
    if (state_ == EState::FALLING) {
        throw std::logic_error("State::to_falling - already falling");
    }
    next_ = next;
    piece_ = falling;
    piece_position_ = position;
    state_ = EState::FALLING;
}

void State::still_falling(const piece::Piece& falling,
      const piece::Position& position) {
    if (state_ != EState::FALLING) {
        throw std::logic_error("State::still_falling - invalid source state");
    }
    piece_ = falling;
    piece_position_ = position;
    state_ = EState::FALLING;
}

void State::to_elimination() {
    if (state_ != EState::FALLING && state_ != EState::ELIMINATING) {
        throw std::logic_error("State::to_eliminating - invalid source state");
    }
    elimination_list_ = board_->elimination_list();
    if (elimination_list_.empty())
        state_ = EState::ELIMINATED;
    else
        state_ = EState::ELIMINATING;
}
}
