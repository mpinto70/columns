#include "MatchController.h"

namespace game {
MatchController::MatchController(piece::SharedBoard& board,
      size_t record)
      : board_(board),
        score_board_(state::Score(record)),
        piece_controller_(board, 4),
        next_({ gui::Color::RED, gui::Color::RED, gui::Color::RED }) {
}

void MatchController::tick() {
    if (piece_controller_.has_piece()) {
    	piece_controller_.step();
    } else {
        piece_controller_.add(next_, 0);
    }
}

state::StatePtr MatchController::state() const {
    if (piece_controller_.has_piece()) {
        return std::make_unique<state::StateFalling>(board_,
              score_board_,
              next_,
              piece_controller_.piece(),
              piece_controller_.position());
    } else {
        return std::make_unique<state::StateInitial>(board_, score_board_);
    }
}
}
