#pragma once

#include "gui/Color.h"

#include <memory>
#include <vector>

namespace piece {
constexpr unsigned char PIECE_SIZE = 3; ///< number of tiles per piece
/** Represents a piece of PIECE_SIZE colored tiles.
    \verbatim
                                          Piece(gui::RED, gui:GREEN, gui::BLUE)
     ___                                         ___
    |   |                                       |   |
    | 0 | <--- color 0                          | 0 | <--- RED
    |___|                                       |___|
    |   |                                       |   |
    | 1 | <--- color 1                          | 1 | <--- GREEN
    |___|                                       |___|
    |   |                                       |   |
    | 2 | <--- color 2                          | 2 | <--- BLUE
    |___|                                       |___|
    \endverbatim
 */
class Piece {
public:
    template <typename... T, std::enable_if_t<sizeof...(T) == PIECE_SIZE, int> = 0>
    constexpr Piece(T&&... values)
          : colors_{ std::forward<T>(values)... } {
    }

    explicit Piece(const gui::Color (&colors)[PIECE_SIZE]);

    void swap(piece::Piece& other);

    /** @return color of the tile indexed by \p i.
     * @param i index (0 <= i < PIECE_SIZE)
     */
    constexpr gui::Color operator[](unsigned char i) const {
        return colors_[i];
    }

    void roll_up();
    void roll_down();

    friend bool operator==(const Piece& lhs, const Piece& rhs) {
        return lhs.colors_ == rhs.colors_;
    }

private:
    std::array<gui::Color, PIECE_SIZE> colors_; ///< the piece
};

constexpr Piece NO_PIECE(gui::Color::NONE, gui::Color::NONE, gui::Color::NONE);
}
