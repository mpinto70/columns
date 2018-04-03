#pragma once

#include "state/ScoreBoard.h"
#include "state/State.h"

namespace state {
bool operator==(const ScoreBoard& lhs, const ScoreBoard& rhs);
bool operator!=(const ScoreBoard& lhs, const ScoreBoard& rhs);
bool operator==(const State& lhs, const State& rhs);
bool operator!=(const State& lhs, const State& rhs);
namespace mck {
StatePtr create_state(piece::SharedConstBoard board);
StatePtr create_state(piece::SharedConstBoard board, const state::ScoreBoard& score_board);
StatePtr create_state(piece::SharedConstBoard board,
      const state::ScoreBoard& score_board,
      const piece::Piece& next,
      const piece::Piece& falling,
      const piece::PiecePosition& position);
StatePtr create_state(piece::SharedConstBoard board,
      const state::ScoreBoard& score_board,
      const piece::Piece& next,
      const EliminationList& elimination);
}
}
