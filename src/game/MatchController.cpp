#include "MatchController.h"

namespace game {
MatchController::MatchController(
      piece::SharedBoard& board,
      size_t record,
      piece::CreatorPtr piece_creator)
      : board_(board),
        score_board_(std::make_shared<state::ScoreBoard>(state::Score(record))),
        piece_creator_(std::move(piece_creator)),
        state_(board, score_board_),
        piece_controller_(board) {}

void MatchController::tick() {
    switch (state_.state()) {
        case state::EState::CLEAN:
            piece_controller_.add(piece_creator_->piece(), piece_creator_->column());
            state_.to_falling(
                  piece_creator_->piece(),
                  piece_controller_.piece(),
                  piece_controller_.position());
            break;
        case state::EState::FALLING:
            if (piece_controller_.step()) {
                state_.still_falling(piece_controller_.piece(), piece_controller_.position());
            } else {
                const auto removed = piece_controller_.remove();
                const auto& piece = removed.first;
                const auto& position = removed.second;
                for (size_t i = 0; i < piece::PIECE_SIZE; ++i) {
                    board_->tile(position.column(), position.row() + i) = piece[i];
                }
                state_.to_elimination();
            }
            break;
        case state::EState::ELIMINATING:
            score_board_->add(state_.elimination_list().size());
            board_->remove(state_.elimination_list());
            state_.to_elimination();
            break;
        case state::EState::ELIMINATED:
            piece_controller_.add(state_.next(), piece_creator_->column());
            state_.to_falling(
                  piece_creator_->piece(),
                  piece_controller_.piece(),
                  piece_controller_.position());
            break;
    }
}

void MatchController::process(EMessage message) {
    piece_controller_.process(message);
    if (state_.state() == state::EState::FALLING) {
        state_.still_falling(piece_controller_.piece(), piece_controller_.position());
    }
}
} // namespace game
