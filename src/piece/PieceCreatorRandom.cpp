#include "PieceCreatorRandom.h"

#include "util/Random.h"

namespace piece {
PieceCreatorRandom::PieceCreatorRandom(const std::vector<gui::Color>& possibles)
      : possibles_(possibles) {
    if (possibles.empty()) {
        throw std::runtime_error("PieceCreatorRandom - possibles was empty");
    }
}

Piece PieceCreatorRandom::get_next() const {
    std::vector<gui::Color> colors;
    colors.reserve(PIECE_SIZE);
    for (size_t i = 0; i < PIECE_SIZE; ++i) {
        const size_t index = util::Random::get(possibles_.size() - 1);
        colors.push_back(possibles_[index]);
    }
    return Piece(colors);
}
}
