#pragma once

#include "piece/Board.h"
#include "piece/Piece.h"
#include "piece/PiecePosition.h"
#include "state/ScoreBoard.h"

#include <memory>

namespace state {
/// tile type to be eliminated from the board
using EliminationItem = std::pair<size_t, size_t>;
/// list of tile type to be eliminated from the board
using EliminationList = std::vector<EliminationItem>;
/// Registers the game state
class State {
public:
    /// Create an initial state (no piece falling).
    State(piece::SharedConstBoard board, const state::ScoreBoard& socre_board);
    /** Create an initial state with a falling piece.
     * @param board         the board
     * @param score_board   the score
     * @param falling       the falling piece
     * @param position      the position of the falling piece
     * @param next          the next piece to fall
     */
    State(piece::SharedConstBoard board,
          const state::ScoreBoard& score_board,
          const piece::Piece& falling,
          const piece::PiecePosition& position,
          const piece::Piece& next);
    /** Create a state in which nothing will be added and there is no piece falling.
     * @param board         the board
     * @param score_board   the score
     * @param list          list of tiles to be removed
     * @param next          the next piece to fall
     */
    State(piece::SharedConstBoard board,
          const state::ScoreBoard& score_board,
          const EliminationList& list,
          const piece::Piece& next);

    piece::SharedConstBoard board() const { return board_; }
    const state::ScoreBoard& score_board() const { return score_board_; }
    bool has_piece_falling() const { return piece_.get() != nullptr; }
    /** @return the position of the current falling piece.
     * @throw std::logic_error if there is no piece falling
     */
    const piece::PiecePosition& piece_position() const;
    /** @return the falling piece.
     * @throw std::logic_error if there is no piece falling
     */
    const piece::Piece& piece() const;
    const EliminationList& elimination_list() const { return elimination_list_; }
    bool has_next() const { return next_.get() != nullptr; }
    /** @return the next piece to fall in the board.
     * @throw std::logic_error if there is no next piece
     */
    const piece::Piece& next() const;

private:
    using PositionPtr = std::unique_ptr<piece::PiecePosition>;
    piece::SharedConstBoard board_;
    state::ScoreBoard score_board_;
    piece::PiecePtr piece_;      ///< the piece falling
    PositionPtr piece_position_; ///< the position of the falling piece
    EliminationList elimination_list_;
    piece::PiecePtr next_; ///< next piece to be put in the board
};
}
