#pragma once

#include "game/PieceController.h"
#include "state/State.h"

namespace game {
class MatchController {
public:
    MatchController(piece::SharedBoard& board,
          size_t record);

    void tick();
    state::StatePtr state() const;

private:
    piece::SharedBoard board_;
    state::ScoreBoard score_board_;
    PieceController piece_controller_;
    piece::Piece next_;
};
}
