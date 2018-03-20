
#include "BoardDrawer.h"

namespace grafico {

namespace {
void draw_tile_(Window& window,
      const gui::Color& color,
      const uint16_t x1,
      const uint16_t y1,
      const uint16_t size) {
    const int x2 = x1 + size - 1;
    const int y2 = y1 + size - 1;
    const gui::Rectangle rect(x1, y1, x2, y2);
    window.fill(rect, color);
    window.rectangle(rect, gui::darken(color, 20));
}
}

BoardDrawer::BoardDrawer(const uint16_t left,
      const uint16_t top,
      const uint16_t tile_size,
      const uint16_t step_size)
      : left_(left),
        top_(top),
        tile_size_(tile_size),
        step_size_(step_size) {
    if (tile_size == 0) {
        throw std::invalid_argument("BoardDrawer - zero tile size");
    }
    if (step_size == 0) {
        throw std::invalid_argument("BoardDrawer - zero step size");
    }
    if (tile_size % step_size != 0) {
        throw std::invalid_argument("BoardDrawer - invalid relation between tile size and step size");
    }
}

void BoardDrawer::draw(Window& window,
      const game::State& state,
      const gui::Color& elimination_color) const {
    draw(window, state.board());
    if (state.has_piece_falling()) {
        const auto& position = state.piece_position();
        const auto& piece = state.piece();
        for (uint16_t i = 0; i < piece::PIECE_SIZE; ++i) {
            draw_tile(window, piece[i], position.column(), position.row() + i, position.sub_row());
        }
    } else {
        for (const auto& eliminated : state.elimination_list()) {
            const auto column = eliminated.first;
            const auto row = eliminated.second;
            draw_tile(window, elimination_color, column, row);
        }
    }
}

void BoardDrawer::draw(Window& window,
      const piece::Board& board) const {
    window.fill(gui::Rectangle(left_,
                      top_,
                      left_ + board.width() * tile_size_,
                      top_ + board.height() * tile_size_),
          board.background_color());
    for (uint16_t i = 0; i < board.width(); ++i) {
        for (uint16_t j = 0; j < board.height(); ++j) {
            const auto& tile_color = board.at(i, j);
            if (tile_color == board.background_color()) {
                continue; // bottom
            }
            draw_tile(window, tile_color, i, j);
        }
    }
}

void BoardDrawer::draw_tile(Window& window,
      const gui::Color& color,
      const uint16_t column,
      const uint16_t row,
      const uint16_t sub_row) const {
    const auto x = column * tile_size_ + left_;
    const auto dy = sub_row * step_size_;
    const int y = row * tile_size_ + dy + top_;
    draw_tile_(window,
          color,
          x,
          y,
          tile_size_);
}
}
