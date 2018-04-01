#include "Piece.h"

#include "util/Random.h"

#include <algorithm>
#include <cstring>
#include <stdexcept>

namespace piece {

Piece::Piece(const gui::Color (&colors)[PIECE_SIZE]) {
    std::memcpy(colors_, colors, sizeof(colors_));
}

Piece::Piece(const std::vector<gui::Color>& colors) {
    if (colors.size() != PIECE_SIZE) {
        throw std::invalid_argument("Piece - vector with invalid size");
    }

    std::copy(colors.begin(), colors.end(), colors_);
}

gui::Color Piece::operator[](unsigned char i) const {
    if (i >= PIECE_SIZE) {
        throw std::range_error("Piece[" + std::to_string(i) + "] - index out of range");
    }
    return colors_[i];
}

void Piece::roll_up() {
    std::rotate(&colors_[0], &colors_[1], &colors_[PIECE_SIZE]);
}

void Piece::roll_down() {
    std::rotate(&colors_[0], &colors_[PIECE_SIZE - 1], &colors_[PIECE_SIZE]);
}

Piece Piece::create(const std::vector<gui::Color>& possible) {
    if (possible.empty()) {
        throw std::invalid_argument("Piece::create - no colors to pick");
    }
    gui::Color colors[PIECE_SIZE];
    std::generate_n(colors, PIECE_SIZE, [&possible]() {
        return possible[util::Random::get(possible.size() - 1)];
    });
    return piece::Piece(colors);
}
}
