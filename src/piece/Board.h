#pragma once

#include "gui/Color.h"
#include "piece/Piece.h"

#include <memory>
#include <vector>

namespace piece {
/// Represents the game board
class Board {
public:
    struct Tile {
        size_t column;
        size_t row;
    };
    using EliminationList = std::vector<Tile>;
    /** Creates an empty board with dimensions \p w X \p h.
     * @param w board width in tile squares
     * @param h board height in tile squares
     */
    Board(size_t w, size_t h);

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
    /// @return board width
    size_t width() const { return width_; }
    /// @return board height
    size_t height() const { return height_; }
    /** Removes the square at position (c, r) and the squares above it fall.
     * @param c column index
     * @param r row index
     */
    void remove(size_t c, size_t r);

    bool used(size_t c, size_t r) const;

    EliminationList elimination_list() const;

private:
    std::vector<gui::Color> tiles_; ///< the board
    size_t width_;                  ///< board width
    size_t height_;                 ///< board height

    void check_overflow(size_t c, size_t r) const;

    bool has_horizontal_triplet(size_t c,
          size_t r,
          gui::Color color) const;
    bool has_vertical_triplet(size_t c,
          size_t r,
          gui::Color color) const;
    bool has_diagonal_descending_triplet(size_t c,
          size_t r,
          gui::Color color) const;
    bool has_diagonal_ascending_triplet(size_t c,
          size_t r,
          gui::Color color) const;
    void add_horizontal_triplet(std::vector<Tile>& res,
          size_t i,
          size_t j) const;
    void add_vertical_triplet(std::vector<Tile>& res,
          size_t i,
          size_t j) const;
    void add_diagonal_descending_triplet(std::vector<Tile>& res,
          size_t i,
          size_t j) const;
    void add_diagonal_ascending_triplet(std::vector<Tile>& res,
          size_t i,
          size_t j) const;
};

constexpr bool operator==(const Board::Tile& lhs, const Board::Tile& rhs) {
    return lhs.column == rhs.column && lhs.row == rhs.row;
}

constexpr bool operator<(const Board::Tile& lhs, const Board::Tile& rhs) {
    return lhs.column < rhs.column || (lhs.column == rhs.column && lhs.row < rhs.row);
}

using SharedBoard = std::shared_ptr<Board>;
using SharedConstBoard = std::shared_ptr<const Board>;
}
