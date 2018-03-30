#pragma once

#include "graphics/Drawer.h"

#include <cstdint>

namespace graphics {

class BoardDrawer : public Drawer {
public:
    /**
     * @param top_left  board top left corner
     * @param tile_size tile size
     * @param step_size sub tile step size
     */
    BoardDrawer(const gui::Point& top_left,
          uint16_t tile_size,
          uint16_t step_size,
          const gui::Color& elimination_color);

    ~BoardDrawer() override = default;

    void draw(Window& window, const state::State& state) const override;

private:
    gui::Point top_left_;          ///< board top left corner
    uint16_t tile_size_;           ///< tile size
    uint16_t step_size_;           ///< sub tile step size
    gui::Color elimination_color_; ///< color for the tiles being eliminated

    void draw(Window& window,
          const piece::Board& board) const;

    void draw_tile(Window& windows,
          const gui::Color& color,
          uint16_t column,
          uint16_t row,
          uint16_t sub_row = 0) const;
};
}
