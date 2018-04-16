#pragma once

#include "piece/Board.h"
#include "piece/Piece.h"
#include "piece/PiecePosition.h"
#include "state/State.h"

#include <memory>

namespace game {
/** Coordinates interaction with the board:
 * \li informs if it is possible to add piece;
 * \li put a new falling piece;
 * \li move the piece right and left;
 * \li roll the falling piece;
 * \li show and perform tiles removal.
 */
class BoardController {
public:
    BoardController(piece::SharedBoard board, size_t max_sub_row);
    BoardController(const BoardController&) = delete;
    BoardController& operator=(const BoardController&) = delete;
    piece::SharedConstBoard board() const { return board_; }
    /** Add a piece to the board
     * @param piece the piece
     * @return true if it was possible to add a piece
     * @return false otherwise
     * @throw std::logic_error if there is a piece falling
     */
    bool add_piece(const piece::Piece& piece);
    bool has_piece() const { return piece_.get() != nullptr; }
    /**
     * @throw std::logic_error if there is no piece falling
     */
    const piece::PiecePosition& piece_position() const;
    /** @return the piece that is falling.
     * @throw std::logic_error if there is no piece falling
     */
    const piece::Piece& piece() const;
    /** Step the falling piece. */
    void step();
    void move_left();
    void move_right();
    void roll_up();
    void roll_down();
    /** @return the list of tiles to eliminate. */
    piece::Board::EliminationList determine_elimination() const;
    /// Eliminate the tiles.
    void eliminate(const piece::Board::EliminationList& tiles);

private:
    using PositionPtr = std::unique_ptr<piece::PiecePosition>;
    piece::SharedBoard board_;
    piece::PiecePtr piece_; ///< the piece falling in the board
    PositionPtr piece_position_;
    const size_t max_sub_row_;
    const std::vector<gui::Color> possibles_;

    bool can_move_to(size_t column) const;
    /** @return determine where a new piece can be inserted.
     * @attention if there is no column available, returns width
     */
    size_t determine_column() const;
    bool can_add_piece(size_t column) const;
    /** @return if the piece has reached end of its fall. */
    bool reached_end() const;
};
}
