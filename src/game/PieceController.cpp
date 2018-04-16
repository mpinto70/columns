#include "PieceController.h"

#include <chrono>
#include <iostream>
#include <thread>

namespace game {
PieceController::PieceController(piece::SharedConstBoard board,
      size_t max_sub_row)
      : board_(board),
        max_sub_row_(max_sub_row),
        piece_(nullptr),
        position_(nullptr),
        steps_per_step_(1) {
}

piece::PiecePosition PieceController::position() const {
    if (not position_)
        throw std::runtime_error("PieceController::position - no piece falling");
    return *position_;
}

piece::Piece PieceController::piece() const {
    if (not piece_)
        throw std::runtime_error("PieceController::piece - no piece falling");
    return *piece_;
}

void PieceController::add(const piece::Piece& piece, size_t column) {
    if (board_->used(column, piece::PIECE_SIZE - 1))
        throw std::runtime_error("PieceController::add - invalid column");
    auto pic = std::make_unique<piece::Piece>(piece);
    auto pos = std::make_unique<piece::PiecePosition>(*board_, column, max_sub_row_);
    steps_per_step_ = 1;
    piece_.swap(pic);
    position_.swap(pos);
}

void PieceController::process(const Messages::List& messages) {
    if (not position_)
        throw std::runtime_error("PieceController::process - no piece falling");
    for (const auto message : messages) {
        switch (message) {
            case EMessage::MoveLeft:
                if (can_move_left())
                    position_->move_left();
                break;
            case EMessage::MoveRight:
                if (can_move_right())
                    position_->move_right();
                break;
            case EMessage::RollUp:
                piece_->roll_up();
                break;
            case EMessage::RollDown:
                piece_->roll_down();
                break;
            case EMessage::DropDown:
                steps_per_step_ = 5;
                break;
            default:
                break;
        }
    }
}

bool PieceController::step() {
    if (not position_)
        throw std::runtime_error("PieceController::step - no piece falling");
    for (size_t i = 0; i < steps_per_step_; ++i) {
        if (not can_step_down())
            return false;
        position_->step_down();
    }
    return true;
}

bool PieceController::can_move_left() const {
    const auto column = position_->column();
    const auto bottom_row = lower_row_to_check();
    if (column == 0)
        return false;
    if (board_->used(column - 1, bottom_row))
        return false;
    return true;
}

bool PieceController::can_move_right() const {
    const auto column = position_->column();
    const auto bottom_row = lower_row_to_check();
    if (column + 1 == board_->width())
        return false;
    if (board_->used(column + 1, bottom_row))
        return false;

    return true;
}

bool PieceController::can_step_down() const {
    const auto column = position_->column();
    const auto row = position_->row();
    if (row + piece::PIECE_SIZE == board_->height())
        return false;
    if (board_->used(column, row + piece::PIECE_SIZE))
        return false;
    return position_->row() + piece::PIECE_SIZE < board_->height();
}

size_t PieceController::lower_row_to_check() const {
    return position_->row() + piece::PIECE_SIZE - (position_->sub_row() == 0 ? 1 : 0);
}
}
