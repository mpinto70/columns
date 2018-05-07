#pragma once

#include "game/PieceController.h"
#include "piece/PieceCreator.h"
#include "state/State.h"

namespace game {
class MatchController {
public:
    MatchController(piece::SharedBoard& board,
          size_t record,
          piece::PieceCreatorPtr&& piece_creator);

    void tick();
    void process(EMessage message);

    state::StatePtr state() const;

private:
    piece::SharedBoard board_;
    state::ScoreBoard score_board_;
    piece::PieceCreatorPtr piece_creator_;
    PieceController piece_controller_;
    piece::Piece next_;
};
}
