#pragma once

#include "game/BoardController.h"
#include "game/Messages.h"
#include "gui/Color.h"
#include "piece/Board.h"
#include "state/Score.h"
#include "state/ScoreBoard.h"
#include "state/StateObserver.h"

#include <atomic>
#include <mutex>

namespace game {
/** Controls the game:
 * \li controls the board;
 * \li controls the score board.
 */
class GameController {
public:
    GameController(piece::SharedBoard board,
          size_t max_sub_row,
          const state::Score& record,
          const std::vector<gui::Color>& possible,
          state::StateObserverPtr&& observer,
          SharedMessage& msg);
    GameController(const GameController&) = delete;
    GameController& operator=(const GameController&) = delete;
    /** execution loop. */
    void execute();

private:
    BoardController board_controller_;
    state::ScoreBoard score_board_;
    piece::Piece next_piece_;
    std::vector<gui::Color> possible_;
    state::StateObserverPtr observer_;
    SharedMessage messages_;
    std::atomic<bool> should_stop_; ///< indicates if the player pressed ESC
    state::StatePtr prepare_state(const state::EliminationList& elimination_list = state::EliminationList()) const;
    void process(const Messages::List& msgs);
};
}
