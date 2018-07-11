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

Piece Piece::create(const std::vector<gui::Color>& possibles) {
    if (possibles.empty()) {
        throw std::invalid_argument("Piece::create - no colors to pick");
    }
    gui::Color colors[PIECE_SIZE];
    std::generate_n(colors, PIECE_SIZE, [&possibles]() {
        return possibles[util::Random::get(possibles.size() - 1)];
    });
    return piece::Piece(colors);
}
}
