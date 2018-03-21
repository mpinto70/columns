#pragma once

#include "game/BoardController.h"
#include "game/Message.h"
#include "game/StateObserver.h"
#include "gui/Color.h"
#include "piece/Board.h"
#include "score/Score.h"
#include "score/ScoreBoard.h"

#include <atomic>
#include <mutex>

namespace game {
/** Controls the game:
 * \li controls the board;
 * \li controls the score board.
 */
class GameController {
public:
    GameController(const piece::Board& board,
          uint16_t max_sub_row,
          const score::Score& record,
          const std::vector<gui::Color>& possible,
          StateObserverPtr&& observer,
          MensagemPtr& msg);
    GameController(const GameController&) = delete;
    GameController& operator=(const GameController&) = delete;
    /** execution loop. */
    void execute();

private:
    BoardController board_controller_;
    score::ScoreBoard score_board_;
    piece::Piece next_piece_;
    std::vector<gui::Color> possible_;
    StateObserverPtr observer_;
    MensagemPtr messages_;
    std::atomic<bool> should_stop_; ///< indicates if the player pressed ESC
    State prepare_state(const game::EliminationList& elimination_list = game::EliminationList()) const;
    void process(const Message::Lista& msgs);
};
}
