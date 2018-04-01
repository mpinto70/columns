#include "Board.h"

#include <stdexcept>
#include <utility>

namespace piece {

Board::Board(const size_t w,
      const size_t h,
      gui::Color background)
      : tiles_(w * h, background),
        background_color_(background),
        width_(w),
        height_(h) {
    if (w < PIECE_SIZE) {
        throw std::invalid_argument("Board - insufficient width");
    }
    if (h < 2 * PIECE_SIZE) {
        throw std::invalid_argument("Board - insufficient height");
    }
}

gui::Color Board::at(const size_t c, const size_t r) const {
    check_overflow(c, r);
    return tiles_.at(r * width_ + c);
}

gui::Color& Board::at(const size_t c, const size_t r) {
    check_overflow(c, r);
    return tiles_.at(r * width_ + c);
}

void Board::remove(const size_t c, const size_t r) {
    for (size_t j = r; j > 0; --j) {
        at(c, j) = at(c, j - 1);
    }
    at(c, 0) = background_color_;
}

void Board::check_overflow(size_t c, size_t r) const {
    if (c >= width_) {
        throw std::invalid_argument("Board::at - column overflow " + std::to_string(c));
    }
    if (r >= height_) {
        throw std::invalid_argument("Board::at - row overflow " + std::to_string(r));
    }
}
}
