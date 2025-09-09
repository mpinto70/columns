#pragma once

#include "game/PieceController.h"
#include "piece/Creator.h"
#include "state/State.h"

namespace game {
class MatchController {
public:
    MatchController(piece::SharedBoard& board, size_t record, piece::CreatorPtr piece_creator);

    void tick();
    void process(EMessage message);

    [[nodiscard]] const state::State& state() const { return state_; }

private:
    piece::SharedBoard board_;
    state::SharedScoreBoard score_board_;
    piece::CreatorPtr piece_creator_;
    state::State state_;
    PieceController piece_controller_;
};
} // namespace game
