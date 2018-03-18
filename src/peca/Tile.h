#pragma once

#include "gui/Color.h"

#include <memory>
#include <vector>

namespace peca {
constexpr unsigned char TILE_SIZE = 3; ///< number of squares per tile
/** Represents a tile of TILE_SIZE colored squares.
    \verbatim
                                        Tile(gui::RED, gui::BLUE, gui:GREEN)
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
class Tile {
public:
    explicit Tile(const gui::Color (&colors)[TILE_SIZE]);
    explicit Tile(const std::vector<gui::Color>& colors);
    /** @return color of the square indexed by \p i.
     * @param i index (0 <= i <= 2)
     * @throws std::invalid_argument if \p i is out of bounds
     */
    const gui::Color& operator[](unsigned char i) const;
    void roll_up();
    void roll_down();
    /** @return create a tile with random colors based on colors from \p possibles.
     * @param possibles the allowed colors.
     */
    static Tile create(const std::vector<gui::Color>& possibles);

private:
    gui::Color colors_[TILE_SIZE]; ///< the tile
    friend bool operator==(const Tile& lhs, const Tile& rhs);
};

bool operator==(const Tile& lhs, const Tile& rhs);
bool operator!=(const Tile& lhs, const Tile& rhs);
typedef std::unique_ptr<Tile> TilePtr;
}
