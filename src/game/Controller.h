#pragma once

#include "game/Canvas.h"
#include "game/InputReader.h"
#include "state/State.h"

namespace game {

class Controller {
public:
    Controller(CanvasPtr&& canvas,
          InputReaderPtr&& input_reader,
          piece::SharedBoard& board,
          size_t record);
    void run();
    const state::State& state() const { return *state_; }

private:
    CanvasPtr canvas_;
    InputReaderPtr input_reader_;
    piece::SharedBoard board_;
    state::ScoreBoard score_board_;
    state::StatePtr state_;

    void process_inputs();
    void process_input(EMessage input);
};
}
