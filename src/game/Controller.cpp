#include "Controller.h"

#include "state/State.h"
#include "util/Wait.h"

namespace game {
namespace {
void draw_state(graphics::Window& window,
      const state::State& state,
      const graphics::DrawerList& drawers) {
    for (auto& drawer : drawers) {
        drawer->draw(window, state);
    }
}
}

Controller::Controller(graphics::WindowPtr&& window,
      graphics::DrawerList&& drawers,
      InputReaderPtr&& input_reader,
      const piece::Board& board,
      size_t record)
      : window_(std::move(window)),
        drawers_(std::move(drawers)),
        input_reader_(std::move(input_reader)),
        state_(board, state::ScoreBoard(state::Score(record), state::Score(0))) {
}

void Controller::run() {
    window_->clear();
    draw_state(*window_, state_, drawers_);
}
}
