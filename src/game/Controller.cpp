#include "Controller.h"

#include <utility>

namespace game {

Controller::Controller(CanvasPtr&& canvas,
      InputReaderPtr&& input_reader,
      size_t board_width,
      size_t board_height,
      gui::Color board_background,
      size_t record)
      : canvas_(std::move(canvas)),
        input_reader_(std::move(input_reader)),
        board_(std::make_shared<piece::Board>(board_width, board_height, board_background)),
        record_(record) {
}

void Controller::run() {
    state::State state(board_, state::ScoreBoard(state::Score(record_), state::Score(0)));
    canvas_->draw(state);
}
}
