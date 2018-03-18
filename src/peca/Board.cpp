#include "Board.h"

#include <stdexcept>
#include <utility>

namespace peca {

Board::Board(const uint16_t w,
      const uint16_t h,
      const gui::Color& color)
      : tiles_(w * h, color),
        background_color_(color),
        width_(w),
        height_(h) {
    if (w < PIECE_SIZE) {
        throw std::invalid_argument("Board - insufficient width");
    }
    if (h < 2 * PIECE_SIZE) {
        throw std::invalid_argument("Board - insufficient height");
    }
}

const gui::Color& Board::at(const uint16_t c, const uint16_t r) const {
    if (c >= width_) {
        throw std::invalid_argument("Board::at const - column overflow " + std::to_string(c));
    }
    if (r >= height_) {
        throw std::invalid_argument("Board::at const - row overflow " + std::to_string(r));
    }
    return tiles_.at(r * width_ + c);
}

gui::Color& Board::at(const uint16_t c, const uint16_t r) {
    if (c >= width_) {
        throw std::invalid_argument("Board::at - column overflow " + std::to_string(c));
    }
    if (r >= height_) {
        throw std::invalid_argument("Board::at - row overflow " + std::to_string(r));
    }
    return tiles_.at(r * width_ + c);
}

void Board::remove(const uint16_t c, const uint16_t r) {
    for (uint16_t j = r; j > 0; --j) {
        at(c, j) = at(c, j - 1);
    }
    at(c, 0) = background_color_;
}

bool operator==(const Board& lhs, const Board& rhs) {
    return lhs.height() == rhs.height()
           && lhs.width() == rhs.width()
           && lhs.tiles() == rhs.tiles();
    return true;
}

bool operator!=(const Board& lhs, const Board& rhs) {
    return not(lhs == rhs);
}
}
