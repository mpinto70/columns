#pragma once

#include "piece/Board.h"

#include <cstddef>
#include <cstdint>

namespace piece {

/// Represents the position of a piece in a board
class PiecePosition {
public:
    /**
     * @param board the board
     * @param col column
     * @param max_sub_row the maximum divisions in a step
     */
    PiecePosition(const Board& board,
          uint16_t col,
          uint16_t max_sub_row);
    /** step down.
     * @throw std::logic_error if it is not possible to step down
     */
    void step_down();
    uint16_t column() const { return column_; }
    uint16_t row() const { return row_; }
    uint16_t sub_row() const { return sub_row_; }
    uint16_t max_sub_row() const { return max_sub_row_; }
    uint16_t max_column() const { return max_column_; }
    uint16_t max_row() const { return max_row_; }
    void move_left();
    void move_right();
    bool reached_bottom() const { return row_ + PIECE_SIZE == max_row_; }

private:
    uint16_t column_;      ///< column where the piece is
    uint16_t row_;         ///< row where the piece is
    uint16_t sub_row_;     ///< sub row where the piece is
    uint16_t max_sub_row_; ///< maximum number of divisions in a step down
    uint16_t max_column_;  ///< maximum columns position
    uint16_t max_row_;     ///< maximum row position
};
}
