#include "Piece.h"

#include "util/Random.h"

#include <algorithm>
#include <cstring>
#include <stdexcept>

namespace piece {

Piece::Piece(const gui::Color (&colors)[PIECE_SIZE]) {
    std::memcpy(colors_.data(), colors, PIECE_SIZE * sizeof(gui::Color));
}

void Piece::swap(piece::Piece& other) {
    std::swap_ranges(colors_.begin(), colors_.end(), other.colors_.begin());
}

void Piece::roll_up() {
    std::rotate(&colors_[0], &colors_[1], &colors_[PIECE_SIZE]);
}

void Piece::roll_down() {
    std::rotate(&colors_[0], &colors_[PIECE_SIZE - 1], &colors_[PIECE_SIZE]);
}
}
