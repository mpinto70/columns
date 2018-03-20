#pragma once

#include "gui/Color.h"
#include "jogo/BoardController.h"
#include "jogo/Message.h"
#include "jogo/StateObserver.h"
#include "piece/Board.h"
#include "score/Score.h"
#include "score/ScoreBoard.h"

#include <atomic>
#include <mutex>

namespace jogo {
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
    State prepare_state(const jogo::EliminationList& elimination_list = jogo::EliminationList()) const;
    void process(const Message::Lista& msgs);
};
}
