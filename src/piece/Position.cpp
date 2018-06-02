#include "Position.h"

#include <stdexcept>

namespace piece {

void Position::step_down() {
    ++sub_row_;
    if (sub_row_ > SUBDIVISIONS) {
        sub_row_ = 0;
        ++row_;
    }
}

void Position::move_left() {
    --column_;
}

void Position::move_right() {
    ++column_;
}
}
