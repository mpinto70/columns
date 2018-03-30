#pragma once

#include "game/InputReader.h"
#include "game/Message.h"
#include "graphics/Drawer.h"
#include "graphics/Window.h"
#include "piece/Board.h"
#include "state/State.h"

namespace game {

class Controller {
public:
    Controller(graphics::WindowPtr&& window,
          graphics::DrawerList&& drawers,
          InputReaderPtr&& input_reader,
          const piece::Board& board,
          size_t record);
    void run();

    const state::State& state() const { return state_; }

private:
    graphics::WindowPtr window_;
    graphics::DrawerList drawers_;
    InputReaderPtr input_reader_;
    state::State state_;
};
}
