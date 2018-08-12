#pragma once

#include "piece/Board.h"
#include "piece/Piece.h"
#include "piece/Position.h"
#include "state/ScoreBoard.h"

#include <memory>

namespace state {
enum class EState {
    CLEAN,
    FALLING,
    ELIMINATING,
    ELIMINATED,
};

/// Registers the game state
class State {
public:
    /// Create an initial state (no piece falling).
    State(piece::SharedConstBoard board, SharedConstScoreBoard score_board);

    EState state() const { return state_; }
    const piece::Board& board() const { return *board_; }
    const ScoreBoard& score_board() const { return *score_board_; }

    bool has_next() const;

    const piece::Piece& next() const;

    bool has_piece_falling() const;

    const piece::Position& piece_position() const;

    const piece::Piece& piece() const;

    bool has_elimination_list() const;
    /// @throw std::logic_error by default
    const piece::Board::EliminationList& elimination_list() const;

    void to_falling(const piece::Piece& next,
          const piece::Piece& falling,
          const piece::Position& position);
    void still_falling(const piece::Piece& falling,
          const piece::Position& position);
    void to_elimination();

private:
    EState state_;
    piece::SharedConstBoard board_;
    SharedConstScoreBoard score_board_;
    piece::Piece next_;
    piece::Piece piece_;
    piece::Position piece_position_;
    piece::Board::EliminationList elimination_list_;
};
}
