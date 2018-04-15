#include "GameController.h"

#include "state/Score.h"
#include "util/Wait.h"

#include <stdexcept>
#include <unistd.h>

namespace game {

GameController::GameController(piece::SharedBoard board,
      const size_t max_sub_row,
      const state::Score& record,
      const std::vector<gui::Color>& possible,
      state::StateObserverPtr&& observer,
      SharedMessage& msg)
      : board_controller_(board, max_sub_row),
        score_board_(record),
        next_piece_(piece::Piece::create(possible)),
        possible_(possible),
        observer_(std::move(observer)),
        messages_(msg),
        should_stop_(false) {
    if (observer_.get() == nullptr) {
        throw std::invalid_argument("BoardController - null observer");
    }
    if (possible_.empty()) {
        throw std::invalid_argument("BoardController - no possible colors");
    }
    if (messages_.get() == nullptr) {
        throw std::invalid_argument("BoardController - null message");
    }
}

void GameController::execute() {
    should_stop_ = false;
    util::Wait step_time(std::chrono::milliseconds{ 10 });

    while (not should_stop_) {
        step_time.reset();
        if (board_controller_.has_piece()) {
            board_controller_.step();
        } else {
            state::EliminationList elimination_list;
            while (not(elimination_list = board_controller_.determine_elimination()).empty()) {
                util::Wait elimination_time(std::chrono::milliseconds{ 300 });
                auto state = prepare_state(elimination_list);
                observer_->update(*state);
                score_board_.add(elimination_list.size());
                board_controller_.eliminate(elimination_list);
                elimination_time.wait();
                messages_->clear();
            }
            step_time.reset();
            if (not board_controller_.add_piece(next_piece_)) {
                return;
            }
            next_piece_ = piece::Piece::create(possible_);
        }
        process(messages_->get());
        auto state = prepare_state();
        observer_->update(*state);
        step_time.wait();
    }
}

state::StatePtr GameController::prepare_state(const state::EliminationList& elimination_list) const {
    if (board_controller_.has_piece()) {
        return std::make_unique<state::StateFalling>(board_controller_.board(),
              score_board_,
              next_piece_,
              board_controller_.piece(),
              board_controller_.piece_position());
    } else {
        return std::make_unique<state::StateElimination>(board_controller_.board(),
              score_board_,
              next_piece_,
              elimination_list);
    }
}

void GameController::process(const Messages::List& msgs) {
    for (const auto msg : msgs) {
        switch (msg) {
            case EMessage::MoveLeft:
                board_controller_.move_left();
                break;
            case EMessage::MoveRight:
                board_controller_.move_right();
                break;
            case EMessage::DropDown:
                while (board_controller_.has_piece()) {
                    board_controller_.step();
                    board_controller_.step();
                    board_controller_.step();
                    board_controller_.step();
                    board_controller_.step();
                    board_controller_.step();
                    auto state = prepare_state();
                    observer_->update(*state);
                }
                break;
            case EMessage::RollDown:
                board_controller_.roll_down();
                break;
            case EMessage::RollUp:
                board_controller_.roll_up();
                break;
            case EMessage::Stop:
                should_stop_ = true;
                break;
        }
        auto state = prepare_state();
        observer_->update(*state);
    }
}
}
