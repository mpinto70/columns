#pragma once

#include "game/State.h"
#include "piece/Board.h"
#include "piece/Piece.h"
#include "piece/PiecePosition.h"

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
    BoardController(const piece::Board& board,
          uint16_t max_sub_row);
    BoardController(const BoardController&) = delete;
    BoardController& operator=(const BoardController&) = delete;
    const piece::Board& board() const { return board_; }
    /** Add a piece to the board
     * @param piece the piece
     * @return true if it was possible to add a piece
     * @return false otherwise
     * @throw std::logic_error if there is a piece falling
     */
    bool add_piece(const piece::Piece& piece);
    bool has_piece() const { return piece_.get() != NULL; }
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
    EliminationList determine_elimination() const;
    /// Eliminate the tiles.
    void eliminate(const EliminationList& tiles);
    State state() const;

private:
    using PositionPtr = std::unique_ptr<piece::PiecePosition>;
    piece::Board board_;
    piece::PiecePtr piece_; ///< the piece falling in the board
    PositionPtr piece_position_;
    const uint16_t max_sub_row_;
    const std::vector<gui::Color> possibles_;

    bool can_move_to(uint16_t column) const;
    /** @return determine where a new piece can be inserted.
     * @attention if there is no column available, returns width
     */
    uint16_t determine_column() const;
    bool can_add_piece(uint16_t column) const;
    /** @return if the piece has reached end of its fall. */
    bool reached_end() const;
    bool should_eliminate(uint16_t column, uint16_t row) const;
};
}
