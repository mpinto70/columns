#include "PiecePosition.h"

#include "piece/Board.h"

#include <stdexcept>

namespace piece {

PiecePosition::PiecePosition(const Board& board,
      const uint16_t col,
      const uint16_t max_sub_row)
      : column_(col),
        row_(0),
        sub_row_(0),
        max_sub_row_(max_sub_row),
        max_column_(board.width()),
        max_row_(board.height()) {
    if (max_sub_row_ == 0) {
        throw std::invalid_argument("PiecePosition - zero maximum subdivision");
    }
    if (col >= board.width()) {
        throw std::invalid_argument("PiecePosition - column is greater than board width");
    }
}

void PiecePosition::step_down() {
    if (row_ + PIECE_SIZE == max_row_) {
        throw std::logic_error("PiecePosition::step_down - already at bottom");
    }
    if (sub_row_ == max_sub_row_ - 1) {
        sub_row_ = 0;
        ++row_;
    } else {
        ++sub_row_;
    }
}

void PiecePosition::move_left() {
    if (column_ == 0) {
        throw std::logic_error("PiecePosition::move_left - impossible to move left");
    }
    --column_;
}

void PiecePosition::move_right() {
    if (column_ + 1 == max_column_) {
        throw std::logic_error("PiecePosition::move_right - impossible to move right");
    }
    ++column_;
}

bool operator==(const PiecePosition& lhs, const PiecePosition& rhs) {
    return lhs.column() == rhs.column()
           && lhs.row() == rhs.row()
           && lhs.sub_row() == rhs.sub_row()
           && lhs.max_sub_row() == rhs.max_sub_row();
}

bool operator!=(const PiecePosition& lhs, const PiecePosition& rhs) {
    return not(lhs == rhs);
}
}