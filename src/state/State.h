#pragma once

#include "piece/Board.h"
#include "piece/Piece.h"
#include "piece/PiecePosition.h"
#include "state/ScoreBoard.h"

#include <memory>

namespace state {
/// Registers the game state
class State {
public:
    /// Create an initial state (no piece falling).
    State(piece::SharedConstBoard board,
          const state::ScoreBoard& socre_board);

    virtual ~State() = 0;

    State(const State&) = delete;
    State& operator=(const State&) = delete;
    State(State&&) = delete;
    State& operator=(State&&) = delete;

    piece::SharedConstBoard board() const { return board_; }
    const state::ScoreBoard& score_board() const { return score_board_; }

    virtual bool has_next() const { return false; }
    /// @throw std::logic_error by default
    virtual const piece::Piece& next() const;

    virtual bool has_piece_falling() const { return false; }
    /// @throw std::logic_error by default
    virtual const piece::PiecePosition& piece_position() const;
    /// @throw std::logic_error by default
    virtual const piece::Piece& piece() const;

    virtual bool has_elimination_list() const { return false; }
    /// @throw std::logic_error by default
    virtual const piece::Board::EliminationList& elimination_list() const;

private:
    piece::SharedConstBoard board_;
    state::ScoreBoard score_board_;
};

using StatePtr = std::unique_ptr<const State>;

class StateInitial : public State {
public:
    StateInitial(piece::SharedConstBoard board,
          const state::ScoreBoard& socre_board);
    ~StateInitial() override = default;
};

class StateWithNext : public State {
public:
    StateWithNext(piece::SharedConstBoard board,
          const state::ScoreBoard& socre_board,
          const piece::Piece& next);
    ~StateWithNext() override = default;

    bool has_next() const override { return true; }
    const piece::Piece& next() const override { return next_; }

private:
    piece::Piece next_;
};

class StateElimination : public StateWithNext {
public:
    /** Create a state in which nothing will be added and there is no piece falling.
     * @param board         the board
     * @param score_board   the score
     * @param next          the next piece to fall
     * @param list          list of tiles to be removed
     */
    StateElimination(piece::SharedConstBoard board,
          const state::ScoreBoard& score_board,
          const piece::Piece& next,
          const piece::Board::EliminationList& list);

    ~StateElimination() override = default;
    bool has_piece_falling() const override { return false; }
    bool has_elimination_list() const override { return true; }
    const piece::Board::EliminationList& elimination_list() const override { return elimination_list_; }

private:
    piece::Board::EliminationList elimination_list_;
};

class StateFalling : public StateWithNext {
public:
    /** Create an initial state with a falling piece.
     * @param board         the board
     * @param score_board   the score
     * @param next          the next piece to fall
     * @param falling       the falling piece
     * @param position      the position of the falling piece
     */
    StateFalling(piece::SharedConstBoard board,
          const state::ScoreBoard& score_board,
          const piece::Piece& next,
          const piece::Piece& falling,
          const piece::PiecePosition& position);

    ~StateFalling() = default;

    bool has_piece_falling() const override { return true; }
    const piece::PiecePosition& piece_position() const override { return piece_position_; }
    const piece::Piece& piece() const override { return piece_; }

private:
    piece::Piece piece_;                  ///< the piece falling
    piece::PiecePosition piece_position_; ///< the position of the falling piece
};
}
