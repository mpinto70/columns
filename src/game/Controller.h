#pragma once

#include "game/Canvas.h"
#include "game/InputReader.h"
#include "game/MatchController.h"
#include "piece/Creator.h"
#include "state/State.h"

namespace game {

class Controller {
public:
    Controller(CanvasPtr&& canvas,
          InputReaderPtr&& input_reader,
          piece::SharedBoard& board,
          size_t record,
          piece::CreatorPtr&& piece_creator);
    void run();
    [[nodiscard]] const state::State& state() const { return match_controller_.state(); }

private:
    CanvasPtr canvas_;
    InputReaderPtr input_reader_;
    MatchController match_controller_;
    piece::SharedBoard board_;
    state::ScoreBoard score_board_;

    void process_inputs();
};
}
