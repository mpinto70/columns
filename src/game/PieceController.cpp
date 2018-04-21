#include "PieceController.h"

#include <chrono>
#include <iostream>
#include <thread>

namespace game {
namespace {
piece::Piece no_piece() {
    return piece::Piece(std::vector<gui::Color>(piece::PIECE_SIZE, gui::Color::NONE));
}
}

PieceController::PieceController(piece::SharedConstBoard board,
      size_t max_sub_row)
      : board_(board),
        max_sub_row_(max_sub_row),
        piece_(no_piece()),
        position_(*board, 0, max_sub_row),
        steps_per_step_(1) {
}
const piece::PiecePosition& PieceController::position() const {
    if (not has_piece())
        throw std::runtime_error("PieceController::position - no piece falling");
    return position_;
}

const piece::Piece& PieceController::piece() const {
    if (not has_piece())
        throw std::runtime_error("PieceController::piece - no piece falling");
    return piece_;
}

void PieceController::add(const piece::Piece& piece, size_t column) {
    if (has_piece())
        throw std::runtime_error("PieceController::add - there is a piece falling");
    if (board_->used(column, piece::PIECE_SIZE - 1))
        throw std::runtime_error("PieceController::add - invalid column");
    position_ = piece::PiecePosition(*board_, column, max_sub_row_);
    piece_ = piece;
    steps_per_step_ = 1;
}

std::pair<piece::Piece, piece::PiecePosition> PieceController::remove() {
    if (not has_piece())
        throw std::runtime_error("PieceController::remove - no piece falling");
    piece::Piece res = no_piece();
    res.swap(piece_);
    return std::make_pair(res, position_);
}

void PieceController::process(EMessage message) {
    if (not has_piece())
        throw std::runtime_error("PieceController::process - no piece falling");
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
        throw std::runtime_error("PieceController::step - no piece falling");
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
    if (board_->used(column - 1, bottom_row))
        return false;
    return true;
}

bool PieceController::can_move_right() const {
    const auto column = position_.column();
    const auto bottom_row = lower_row_to_check();
    if (column + 1 == board_->width())
        return false;
    if (board_->used(column + 1, bottom_row))
        return false;

    return true;
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
