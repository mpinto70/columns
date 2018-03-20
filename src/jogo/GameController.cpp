#include "GameController.h"

#include "score/Score.h"
#include "util/Wait.h"

#include <stdexcept>
#include <unistd.h>

namespace jogo {

GameController::GameController(const piece::Board& board,
      const uint16_t max_sub_row,
      const score::Score& record,
      const std::vector<gui::Color>& possible,
      StateObserverPtr&& observer,
      MensagemPtr& msg)
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
    util::Wait step_time(10);

    while (not should_stop_) {
        step_time.reset();
        if (board_controller_.has_piece()) {
            board_controller_.step();
        } else {
            EliminationList elimination_list;
            while (not(elimination_list = board_controller_.determine_elimination()).empty()) {
                util::Wait elimination_time(300);
                observer_->update(prepare_state(elimination_list));
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
        observer_->update(prepare_state());
        step_time.wait();
    }
}

State GameController::prepare_state(const jogo::EliminationList& elimination_list) const {
    if (board_controller_.has_piece()) {
        return State(board_controller_.board(),
              score_board_,
              board_controller_.piece(),
              board_controller_.piece_position(),
              next_piece_);
    } else {
        return State(board_controller_.board(),
              score_board_,
              elimination_list,
              next_piece_);
    }
}

void GameController::process(const Message::Lista& msgs) {
    for (const auto msg : msgs) {
        switch (msg) {
            case EMessage::MoveLeft:
                board_controller_.move_left();
                break;
            case EMessage::MoveRight:
                board_controller_.move_right();
                break;
            case EMessage::MoveDown:
                while (board_controller_.has_piece()) {
                    board_controller_.step();
                    board_controller_.step();
                    board_controller_.step();
                    board_controller_.step();
                    board_controller_.step();
                    board_controller_.step();
                    observer_->update(prepare_state());
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
        observer_->update(prepare_state());
    }
}
}
