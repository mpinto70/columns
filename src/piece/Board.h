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
     * @param color background color
     */
    Board(uint16_t w, uint16_t h, const gui::Color& color);

    /// @return the colors of the board squares
    const std::vector<gui::Color>& tiles() const { return tiles_; }
    /** @return square in position (c, r).
     * @param c column index
     * @param r row index
     */
    const gui::Color& at(uint16_t c, uint16_t r) const;
    /** @return writable square in position (c, r).
     * @param c column index
     * @param r row index
     */
    gui::Color& at(uint16_t c, uint16_t r);
    /// @return background color.
    const gui::Color& background_color() const { return background_color_; }
    /// @return board width
    uint16_t width() const { return width_; }
    /// @return board height
    uint16_t height() const { return height_; }
    /** Removes the square at position (c, r) and the squares above it fall.
     * @param c column index
     * @param r row index
     */
    void remove(uint16_t c, uint16_t r);

private:
    std::vector<gui::Color> tiles_; ///< the board
    gui::Color background_color_;   ///< board background color
    uint16_t width_;                ///< board width
    uint16_t height_;               ///< board height
};

bool operator==(const Board& lhs, const Board& rhs);
bool operator!=(const Board& lhs, const Board& rhs);
}
