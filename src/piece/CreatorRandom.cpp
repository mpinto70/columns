#include "CreatorRandom.h"
#include "util/Random.h"

namespace piece {
CreatorRandom::CreatorRandom(SharedConstBoard board, const std::vector<gui::Color>& possibles)
      : board_(board),
        possibles_(possibles),
        max_column_(board->width() - 1) {
    if (possibles.empty()) {
        throw std::runtime_error("CreatorRandom - possibles was empty");
    }
}

Piece CreatorRandom::piece() const {
    gui::Color colors[PIECE_SIZE];
    for (size_t i = 0; i < PIECE_SIZE; ++i) {
        const size_t index = util::Random::get(possibles_.size() - 1);
        colors[i] = (possibles_[index]);
    }
    return Piece(colors);
}

size_t CreatorRandom::column() const {
    std::vector<size_t> columns_available;
    columns_available.reserve(board_->width());
    for (size_t i = 0; i < board_->width(); ++i) {
        if (not board_->used(i, PIECE_SIZE - 1))
            columns_available.push_back(i);
    }
    if (columns_available.empty())
        throw std::runtime_error("CreatorRandom::column - no available column");
    const size_t index = util::Random::get(columns_available.size() - 1);
    return columns_available[index];
}
}
