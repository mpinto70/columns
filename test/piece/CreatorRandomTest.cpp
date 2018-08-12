#include "../mck/piece/utilpiece.h"

#include "piece/CreatorRandom.h"

#include <gtest/gtest.h>

#include <stdexcept>

namespace piece {
namespace tst {

using gui::Color;

TEST(CreatorRandomTest, piece) {
    const std::vector<Color> possibles = { Color::RED, Color::GREEN, Color::BLUE };
    auto board = std::make_shared<Board>(4, 18);
    CreatorPtr creator = std::make_unique<CreatorRandom>(board, possibles);
    for (size_t p = 0; p < 1000; ++p) {
        const auto piece = creator->piece();
        for (size_t i = 0; i < PIECE_SIZE; ++i) {
            EXPECT_NE(std::find(possibles.begin(), possibles.end(), piece[i]), possibles.end());
        }
    }
}

TEST(CreatorRandomTest, create_invalid) {
    auto board = std::make_shared<Board>(4, 18);
    const std::vector<Color> empty;
    EXPECT_THROW(CreatorRandom invalid(board, empty), std::runtime_error);
}

TEST(CreatorRandomTest, column) {
    const std::vector<Color> possibles = { Color::RED, Color::GREEN, Color::BLUE };
    auto board = std::make_shared<Board>(4, 18);
    CreatorPtr creator = std::make_unique<CreatorRandom>(board, possibles);
    for (size_t p = 0; p < 1000; ++p) {
        const auto column = creator->column();
        EXPECT_GE(column, 0u);
        EXPECT_LT(column, 4u);
    }
}

TEST(CreatorRandomTest, column_invalid) {
    const std::vector<Color> possibles = { Color::RED, Color::GREEN, Color::BLUE };
    auto board = std::make_shared<Board>(4, 18);
    CreatorPtr creator = std::make_unique<CreatorRandom>(board, possibles);
    piece::mck::fill_board(*board, piece::PIECE_SIZE);
    EXPECT_NO_THROW(creator->column());
    piece::mck::fill_board(*board, piece::PIECE_SIZE - 1);
    EXPECT_THROW(creator->column(), std::runtime_error);
}

TEST(CreatorRandomTest, column_specific) {
    const std::vector<Color> possibles = { Color::RED, Color::GREEN, Color::BLUE };
    auto board = std::make_shared<Board>(4, 18);
    CreatorPtr creator = std::make_unique<CreatorRandom>(board, possibles);
    piece::mck::fill_board(*board, piece::PIECE_SIZE - 1);
    for (size_t c = 0; c < board->width(); ++c) {
        board->tile(c, piece::PIECE_SIZE - 1) = gui::Color::NONE;
        EXPECT_EQ(creator->column(), c);
        board->tile(c, piece::PIECE_SIZE - 1) = gui::Color::RED;
        EXPECT_THROW(creator->column(), std::runtime_error);
    }
}
}
}
