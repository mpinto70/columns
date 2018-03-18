#include "Tile.h"

#include "util/Random.h"

#include <algorithm>
#include <stdexcept>

namespace peca {

Tile::Tile(const gui::Color (&colors)[TILE_SIZE])
      : colors_(colors) {
}

Tile::Tile(const std::vector<gui::Color>& colors) {
    if (colors.size() != TILE_SIZE) {
        throw std::invalid_argument("Tile - vector with invalid size");
    }

    std::copy(colors.begin(), colors.end(), colors_);
}

const gui::Color& Tile::operator[](unsigned char i) const {
    if (i >= TILE_SIZE) {
        throw std::range_error("Tile[" + std::to_string(i) + "] - index out of range");
    }
    return colors_[i];
}

void Tile::roll_up() {
    std::rotate(colors_, colors_ + 1, colors_ + TILE_SIZE);
}

void Tile::roll_down() {
    std::rotate(colors_, colors_ + TILE_SIZE - 1, colors_ + TILE_SIZE);
}

Tile Tile::create(const std::vector<gui::Color>& possible) {
    if (possible.empty()) {
        throw std::invalid_argument("Tile::create - no colors to pick");
    }
    gui::Color colors[TILE_SIZE];
    std::generate_n(colors, TILE_SIZE, [&possible]() {
        return possible[util::Random::get(possible.size() - 1)];
    });
    return peca::Tile(colors);
}

bool operator==(const Tile& lhs, const Tile& rhs) {
    return std::equal(lhs.colors_, lhs.colors_ + TILE_SIZE, rhs.colors_);
}

bool operator!=(const Tile& lhs, const Tile& rhs) {
    return not(lhs == rhs);
}
}
