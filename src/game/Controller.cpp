#include "Controller.h"

namespace game {

Controller::Controller(CanvasPtr&& canvas,
      InputReaderPtr&& input_reader,
      size_t board_width,
      size_t board_height,
      gui::Color board_background,
      size_t record)
      : canvas_(std::move(canvas)),
        input_reader_(std::move(input_reader)),
        state_(piece::Board(board_width, board_height, board_background),
              state::ScoreBoard(state::Score(record), state::Score(0))) {
}

void Controller::run() {
    canvas_->draw(state_);
}
}
