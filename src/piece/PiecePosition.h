#pragma once

#include "piece/Board.h"

#include <memory>

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
          size_t col,
          size_t max_sub_row);
    /** step down.
     * @throw std::logic_error if it is not possible to step down
     */
    void step_down();
    size_t column() const { return column_; }
    size_t row() const { return row_; }
    size_t sub_row() const { return sub_row_; }
    size_t max_sub_row() const { return max_sub_row_; }
    size_t max_column() const { return max_column_; }
    size_t max_row() const { return max_row_; }
    void move_left();
    void move_right();
    bool reached_bottom() const { return row_ + PIECE_SIZE == max_row_; }

private:
    size_t column_;      ///< column where the piece is
    size_t row_;         ///< row where the piece is
    size_t sub_row_;     ///< sub row where the piece is
    size_t max_sub_row_; ///< maximum number of divisions in a step down
    size_t max_column_;  ///< maximum columns position
    size_t max_row_;     ///< maximum row position
};
typedef std::unique_ptr<PiecePosition> PiecePositionPtr;
}
