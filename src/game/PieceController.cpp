#include "PieceController.h"

#include <chrono>
#include <iostream>
#include <thread>

namespace game {
PieceController::PieceController(piece::SharedConstBoard board)
      : board_(board),
        piece_(piece::NO_PIECE),
        position_(0),
        steps_per_step_(1) {
}
const piece::Position& PieceController::position() const {
    return position_;
}

const piece::Piece& PieceController::piece() const {
    return piece_;
}

void PieceController::add(const piece::Piece& piece, size_t column) {
    position_ = piece::Position(column);
    piece_ = piece;
    steps_per_step_ = 1;
}

std::pair<piece::Piece, piece::Position> PieceController::remove() {
    piece::Piece res = piece::NO_PIECE;
    res.swap(piece_);
    return std::make_pair(res, position_);
}

void PieceController::process(EMessage message) {
    if (not has_piece())
        return;
    switch (message) {
        case EMessage::MoveLeft:
            if (can_move_left())
                position_.move_left();
            break;
        case EMessage::MoveRight:
            if (can_move_right())
                position_.move_right();
            break;
        case EMessage::RollUp:
            piece_.roll_up();
            break;
        case EMessage::RollDown:
            piece_.roll_down();
            break;
        case EMessage::DropDown:
            steps_per_step_ = 5;
            break;
        default:
            break;
    }
}

bool PieceController::step() {
    if (not has_piece())
        return false;
    for (size_t i = 0; i < steps_per_step_; ++i) {
        if (not can_step_down())
            return false;
        position_.step_down();
    }
    return true;
}

bool PieceController::can_move_left() const {
    const auto column = position_.column();
    const auto bottom_row = lower_row_to_check();
    if (column == 0)
        return false;
    return not board_->used(column - 1, bottom_row);
}

bool PieceController::can_move_right() const {
    const auto column = position_.column();
    const auto bottom_row = lower_row_to_check();
    if (column + 1 == board_->width())
        return false;
    return not board_->used(column + 1, bottom_row);
}

bool PieceController::can_step_down() const {
    const auto column = position_.column();
    const auto row = position_.row();
    if (row + piece::PIECE_SIZE == board_->height())
        return false;
    if (board_->used(column, row + piece::PIECE_SIZE))
        return false;
    return position_.row() + piece::PIECE_SIZE < board_->height();
}

size_t PieceController::lower_row_to_check() const {
    return position_.row() + piece::PIECE_SIZE - (position_.sub_row() == 0 ? 1 : 0);
}
}
