#pragma once

#include "gui/Color.h"
#include "piece/Piece.h"

#include <memory>
#include <vector>

namespace piece {
/// Represents the game board
class Board {
public:
    /** Creates an empty board with dimensions \p w X \p h.
     * @param w board width in tile squares
     * @param h board height in tile squares
     * @param background background color
     */
    Board(size_t w, size_t h, gui::Color background);

    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;
    Board(Board&&) = delete;
    Board& operator=(Board&&) = delete;

    /// @return the colors of the board squares
    const std::vector<gui::Color>& tiles() const { return tiles_; }
    /** @return square in position (c, r).
     * @param c column index
     * @param r row index
     */
    gui::Color at(size_t c, size_t r) const;
    /** @return writable square in position (c, r).
     * @param c column index
     * @param r row index
     */
    gui::Color& at(size_t c, size_t r);
    /// @return background color.
    gui::Color background_color() const { return background_color_; }
    /// @return board width
    size_t width() const { return width_; }
    /// @return board height
    size_t height() const { return height_; }
    /** Removes the square at position (c, r) and the squares above it fall.
     * @param c column index
     * @param r row index
     */
    void remove(size_t c, size_t r);

private:
    std::vector<gui::Color> tiles_; ///< the board
    gui::Color background_color_;   ///< board background color
    size_t width_;                  ///< board width
    size_t height_;                 ///< board height

    void check_overflow(size_t c, size_t r) const;
};

using SharedBoard = std::shared_ptr<Board>;
using SharedConstBoard = std::shared_ptr<const Board>;
}
