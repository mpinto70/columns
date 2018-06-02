#pragma once

#include <memory>

namespace piece {

/// Represents the position of a piece in a board
class Position {
public:
    static constexpr size_t SUBDIVISIONS = 4;

    constexpr explicit Position(size_t col)
          : column_(col),
            row_(0),
            sub_row_(0) {
    }

    constexpr size_t column() const { return column_; }
    constexpr size_t row() const { return row_; }
    constexpr size_t sub_row() const { return sub_row_; }

    /** step down.
     * @throw std::logic_error if it is not possible to step down
     */
    void step_down();
    void move_left();
    void move_right();

private:
    size_t column_;  ///< column where the piece is
    size_t row_;     ///< row where the piece is
    size_t sub_row_; ///< sub row where the piece is (0 <= sub_row_ <= row_subdivisions_)
};
}
