#include "Board.h"

#include <algorithm>
#include <stdexcept>
#include <utility>

namespace piece {

Board::Board(const size_t w,
      const size_t h)
      : tiles_(w * h, gui::Color::NONE),
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
    return tiles_[index(c, r)];
}

gui::Color& Board::at(const size_t c, const size_t r) {
    check_overflow(c, r);
    return tiles_[index(c, r)];
}

void Board::remove(const size_t c, const size_t r) {
    for (size_t j = r; j > 0; --j) {
        at(c, j) = at(c, j - 1);
    }
    at(c, 0) = gui::Color::NONE;
}

void Board::remove(const EliminationList& elimination_list) {
    for (const auto& elimination : elimination_list) {
        remove(elimination.column, elimination.row);
    }
}

bool Board::used(const size_t c, const size_t r) const {
    return at(c, r) != gui::Color::NONE;
}

Board::EliminationList Board::elimination_list() const {
    EliminationList res;
    res.reserve(height_ * width_);
    for (size_t i = 0; i < width_; ++i) {
        for (size_t j = 0; j < height_; ++j) {
            if (used(i, j)) {
                const auto color = at(i, j);
                if (has_horizontal_triplet(i, j, color)) {
                    add_horizontal_triplet(res, i, j);
                }
                if (has_vertical_triplet(i, j, color)) {
                    add_vertical_triplet(res, i, j);
                }
                if (has_diagonal_descending_triplet(i, j, color)) {
                    add_diagonal_descending_triplet(res, i, j);
                }
                if (has_diagonal_ascending_triplet(i, j, color)) {
                    add_diagonal_ascending_triplet(res, i, j);
                }
            }
        }
    }
    std::sort(res.begin(), res.end());
    res.erase(std::unique(res.begin(), res.end()), res.end());

    return res;
}

void Board::check_overflow(size_t c, size_t r) const {
    if (c >= width_) {
        throw std::invalid_argument("Board::at - column overflow " + std::to_string(c));
    }
    if (r >= height_) {
        throw std::invalid_argument("Board::at - row overflow " + std::to_string(r));
    }
}

gui::Color Board::tile(const size_t c, const size_t r) const {
    return tiles_[index(c, r)];
}

gui::Color& Board::tile(const size_t c, const size_t r) {
    return tiles_[index(c, r)];
}

bool Board::has_horizontal_triplet(size_t c,
      size_t r,
      gui::Color color) const {
    return c + 2 < width_ && tile(c + 1, r) == color && tile(c + 2, r) == color;
}

bool Board::has_vertical_triplet(
      size_t c,
      size_t r,
      gui::Color color) const {
    return r + 2 < height_ && tile(c, r + 1) == color && tile(c, r + 2) == color;
}

bool Board::has_diagonal_descending_triplet(size_t c,
      size_t r,
      gui::Color color) const {
    return c + 2 < width_ && r + 2 < height_ && tile(c + 1, r + 1) == color
           && tile(c + 2, r + 2) == color;
}

bool Board::has_diagonal_ascending_triplet(size_t c,
      size_t r,
      gui::Color color) const {
    return c + 2 < width_ && r >= 2 && tile(c + 1, r - 1) == color
           && tile(c + 2, r - 2) == color;
}

void Board::add_horizontal_triplet(std::vector<Tile>& res,
      size_t i,
      size_t j) const {
    res.push_back({ i + 0, j });
    res.push_back({ i + 1, j });
    res.push_back({ i + 2, j });
}

void Board::add_vertical_triplet(std::vector<Tile>& res,
      size_t i,
      size_t j) const {
    res.push_back({ i, j + 0 });
    res.push_back({ i, j + 1 });
    res.push_back({ i, j + 2 });
}

void Board::add_diagonal_descending_triplet(std::vector<Tile>& res,
      size_t i,
      size_t j) const {
    res.push_back({ i + 0, j + 0 });
    res.push_back({ i + 1, j + 1 });
    res.push_back({ i + 2, j + 2 });
}

void Board::add_diagonal_ascending_triplet(std::vector<Tile>& res,
      size_t i,
      size_t j) const {
    res.push_back({ i + 0, j - 0 });
    res.push_back({ i + 1, j - 1 });
    res.push_back({ i + 2, j - 2 });
}
}
