#include "../mck/piece/utilpeca.h"

#include "piece/Piece.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <stdexcept>

namespace piece {
namespace tst {

using gui::Color;

TEST(TestPiece, create) {
    const Piece p1 = mck::create_piece_ascending(0);
    for (unsigned char i = 0; i < PIECE_SIZE; ++i) {
        Color color(i, i, i);
        EXPECT_EQ(p1[i], color);
    }
    EXPECT_THROW(p1[PIECE_SIZE], std::range_error);

    const Piece p2 = mck::create_piece_descending(15);
    for (unsigned char i = 0; i < PIECE_SIZE; ++i) {
        Color color(15 - i, 15 - i, 15 - i);
        EXPECT_EQ(p2[i], color);
    }
    EXPECT_THROW(p2[PIECE_SIZE], std::range_error);

    Piece p3(p1);
    for (unsigned char i = 0; i < PIECE_SIZE; ++i) {
        Color color(i, i, i);
        EXPECT_EQ(p3[i], color);
    }
    EXPECT_THROW(p3[PIECE_SIZE], std::range_error);
    EXPECT_EQ(p3, p1);

    p3 = p2;
    for (unsigned char i = 0; i < PIECE_SIZE; ++i) {
        Color color(15 - i, 15 - i, 15 - i);
        EXPECT_EQ(p3[i], color);
    }
    EXPECT_THROW(p3[PIECE_SIZE], std::range_error);
    EXPECT_EQ(p3, p2);

    Piece p4(p1);
    EXPECT_EQ(p4, p1);
    EXPECT_EQ(p3, p2);
}

TEST(TestPiece, roll) {
    Piece p(mck::create_piece_ascending(0));
    std::vector<unsigned char> colors;
    for (unsigned char i = 0; i < PIECE_SIZE; ++i) {
        colors.push_back(i);
    }

    for (unsigned char i = 0; i < PIECE_SIZE; ++i) {
        const Color color(colors[i], colors[i], colors[i]);
        EXPECT_EQ(p[i], color);
        const Color color0(i, i, i);
        EXPECT_EQ(p[i], color0);
    }

    p.roll_down();
    for (unsigned char i = PIECE_SIZE - 1; i > 0; --i) { // rolling down
        std::swap(colors[i], colors[i - 1]);
    }
    for (unsigned char i = 0; i < PIECE_SIZE; ++i) {
        const Color color(colors[i], colors[i], colors[i]);
        EXPECT_EQ(p[i], color);
    }

    p.roll_down();
    for (unsigned char i = PIECE_SIZE - 1; i > 0; --i) { // rolling down
        std::swap(colors[i], colors[i - 1]);
    }
    for (unsigned char i = 0; i < PIECE_SIZE; ++i) {
        const Color color(colors[i], colors[i], colors[i]);
        EXPECT_EQ(p[i], color);
    }

    p.roll_up();
    for (unsigned char i = 1; i < PIECE_SIZE; ++i) { // rolling up
        std::swap(colors[i - 1], colors[i]);
    }
    for (unsigned char i = 0; i < PIECE_SIZE; ++i) {
        const Color color(colors[i], colors[i], colors[i]);
        EXPECT_EQ(p[i], color);
    }

    p.roll_up();

    for (unsigned char i = 1; i < PIECE_SIZE; ++i) { // rolling up
        std::swap(colors[i - 1], colors[i]);
    }
    for (unsigned char i = 0; i < PIECE_SIZE; ++i) {
        const Color color(colors[i], colors[i], colors[i]);
        EXPECT_EQ(p[i], color);
        const Color color0(i, i, i);
        EXPECT_EQ(p[i], color0);
    }
}

namespace {
void check_colors(const int line,
      const Piece& p,
      const std::vector<gui::Color>& colors) {
    for (unsigned char i = 0; i < PIECE_SIZE; ++i) {
        const auto& color = p[i];
        EXPECT_TRUE(std::find(colors.cbegin(), colors.cend(), color) != colors.cend()) << line;
    }
}

void check_colors(const int line, const std::vector<gui::Color>& colors) {
    for (unsigned char i = 0; i < 100; ++i) {
        const auto p = Piece::create(colors);
        check_colors(line, p, colors);
    }
}
}

TEST(TestPiece, create_piece) {
    std::vector<gui::Color> colors;

    colors.emplace_back(1, 2, 3);
    const auto p1 = Piece::create(colors);
    EXPECT_EQ(p1, Piece(std::vector<gui::Color>(PIECE_SIZE, { 1, 2, 3 })));

    check_colors(__LINE__, colors);

    colors.emplace_back(1, 2, 3);
    EXPECT_EQ(Piece::create(colors), p1);
    check_colors(__LINE__, colors);

    colors.emplace_back(4, 5, 6);
    check_colors(__LINE__, colors);

    colors.emplace_back(10, 153, 12);
    check_colors(__LINE__, colors);
}
}
}
