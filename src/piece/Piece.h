#pragma once

#include "gui/Color.h"

#include <memory>
#include <vector>

namespace piece {
constexpr unsigned char PIECE_SIZE = 3; ///< number of tiles per piece
/** Represents a piece of PIECE_SIZE colored tiles.
    \verbatim
                                          Piece(gui::RED, gui::BLUE, gui:GREEN)
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
    explicit Piece(const gui::Color (&colors)[PIECE_SIZE]);
    explicit Piece(const std::vector<gui::Color>& colors);
    /** @return color of the tile indexed by \p i.
     * @param i index (0 <= i <= PIECE_SIZE)
     * @throws std::invalid_argument if \p i is out of bounds
     */
    const gui::Color& operator[](unsigned char i) const;
    void roll_up();
    void roll_down();
    /** @return create a piece with random colors based on colors from \p possibles.
     * @param possibles the allowed colors.
     */
    static Piece create(const std::vector<gui::Color>& possibles);

private:
    gui::Color colors_[PIECE_SIZE]; ///< the piece
    friend bool operator==(const Piece& lhs, const Piece& rhs);
};

typedef std::unique_ptr<Piece> PiecePtr;
}
