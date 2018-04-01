#pragma once

#include "graphics/Drawer.h"

namespace graphics {

class BoardDrawer : public Drawer {
public:
    /**
     * @param top_left  board top left corner
     * @param tile_size tile size
     * @param step_size sub tile step size
     */
    BoardDrawer(const gui::Point& top_left,
          size_t tile_size,
          size_t step_size,
          gui::Color elimination_color);

    ~BoardDrawer() override = default;

    void draw(Window& window, const state::State& state) const override;

private:
    gui::Point top_left_;          ///< board top left corner
    size_t tile_size_;             ///< tile size
    size_t step_size_;             ///< sub tile step size
    gui::Color elimination_color_; ///< color for the tiles being eliminated

    void draw(Window& window,
          piece::SharedConstBoard board) const;

    void draw_tile(Window& windows,
          gui::Color color,
          size_t column,
          size_t row,
          size_t sub_row = 0) const;
};
}
