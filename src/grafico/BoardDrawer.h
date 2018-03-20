#pragma once

#include "game/State.h"
#include "grafico/Window.h"

#include <cstdint>

namespace grafico {

class BoardDrawer {
public:
    /**
     * @param left      X coordinates of the board top left corner
     * @param top       Y coordinates of the board top left corner
     * @param tile_size tile size
     * @param step_size sub tile step size
     */
    BoardDrawer(uint16_t left,
          uint16_t top,
          uint16_t tile_size,
          uint16_t step_size);

    void draw(Window& window,
          const game::State& state,
          const gui::Color& elimination_color) const;

private:
    uint16_t left_;               ///< X coordinates of the board top left corner
    uint16_t top_;                ///< Y coordinates of the board top left corner
    uint16_t tile_size_; ///< tile size
    uint16_t step_size_;    ///< sub tile step size

    void draw(Window& window,
          const piece::Board& board) const;

    void draw_tile(Window& windows,
          const gui::Color& color,
          uint16_t column,
          uint16_t row,
          uint16_t sub_row = 0) const;
};
}
