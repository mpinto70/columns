#pragma once

#include "game/Canvas.h"
#include "game/InputReader.h"
#include "state/State.h"

namespace game {

class Controller {
public:
    Controller(CanvasPtr&& canvas,
          InputReaderPtr&& input_reader,
          size_t board_width,
          size_t board_height,
          gui::Color board_background,
          size_t record);
    void run();

private:
    CanvasPtr canvas_;
    InputReaderPtr input_reader_;
    piece::SharedBoard board_;
    size_t record_;
};
}
