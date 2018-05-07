#include "MatchController.h"

namespace game {
MatchController::MatchController(piece::SharedBoard& board,
      size_t record,
      piece::PieceCreatorPtr&& piece_creator)
      : board_(board),
        score_board_(state::Score(record)),
        piece_creator_(std::move(piece_creator)),
        piece_controller_(board, 4),
        next_(piece_creator_->get_next()) {
}

void MatchController::tick() {
    if (piece_controller_.has_piece()) {
        if (not piece_controller_.step()) {
            const auto removed = piece_controller_.remove();
            for (size_t i = 0; i < piece::PIECE_SIZE; ++i) {
                board_->at(removed.second.column(), removed.second.row() + i) = removed.first[i];
            }
        }
    } else {
        piece_controller_.add(next_, 0);
    }
}

void MatchController::process(EMessage message) {
    piece_controller_.process(message);
}

state::StatePtr MatchController::state() const {
    if (piece_controller_.has_piece()) {
        return std::make_unique<state::StateFalling>(board_,
              score_board_,
              next_,
              piece_controller_.piece(),
              piece_controller_.position());
    } else {
        const auto elimination_list = board_->elimination_list();
        if (elimination_list.empty())
            return std::make_unique<state::StateInitial>(board_, score_board_);
        else
            return std::make_unique<state::StateElimination>(board_, score_board_, next_, elimination_list);
    }
}
}
