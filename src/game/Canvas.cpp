#include "Canvas.h"

#include <stdexcept>

namespace game {

void Canvas::draw(const state::State& state) {
    clear();
    draw_(state.board());
    draw_(state.score_board());
    if (state.has_piece_falling()) {
        draw_(state.piece(), state.piece_position());
    }
    draw_(state.elimination_list());
    if (state.has_next()) {
        draw_next_(state.next());
    }
}
}
