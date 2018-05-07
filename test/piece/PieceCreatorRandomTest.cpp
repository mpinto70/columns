#include "piece/PieceCreatorRandom.h"

#include <gtest/gtest.h>

#include <stdexcept>

namespace piece {
namespace tst {

using gui::Color;
TEST(PieceCreatorRandomTest, get_next) {
    const std::vector<Color> possibles = { Color::RED, Color::GREEN, Color::BLUE };
    PieceCreatorPtr creator = std::make_unique<PieceCreatorRandom>(possibles);
    const auto piece = creator->get_next();
    for (size_t i = 0; i < PIECE_SIZE; ++i) {
        EXPECT_NE(std::find(possibles.begin(), possibles.end(), piece[i]), possibles.end());
    }
}

TEST(PieceCreatorRandomTest, create_invalid) {
    const std::vector<Color> empty;
    EXPECT_THROW(PieceCreatorRandom invalid(empty), std::runtime_error);
}
}
}
