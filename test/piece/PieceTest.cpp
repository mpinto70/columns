#include "../mck/gui/utilgui.h"
#include "../mck/piece/utilpiece.h"
#include "../mck/util/utiltest.h"

#include "piece/Piece.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <stdexcept>

namespace piece {
namespace tst {

using gui::Color;

TEST(PieceTest, create) {
    const Piece p1 = mck::create_piece_ascending(0);
    for (unsigned char i = 0; i < PIECE_SIZE; ++i) {
        size_t index_color = i % gui::mck::end_color();
        Color color = ::gui::mck::to_color(index_color);
        EXPECT_EQ(p1[i], color);
    }

    const Piece p2 = mck::create_piece_descending(15);
    for (unsigned char i = 0; i < PIECE_SIZE; ++i) {
        size_t index_color = (15 - i) % gui::mck::end_color();
        Color color = ::gui::mck::to_color(index_color);
        EXPECT_EQ(p2[i], color);
    }

    ::mck::check_assignment(__FILE__, __LINE__, p1, p2);
}

TEST(PieceTest, create_constexpr) {
    constexpr Piece piece(Color::RED, Color::GREEN, Color::BLUE);
    EXPECT_EQ(piece[0], Color::RED);
    EXPECT_EQ(piece[1], Color::GREEN);
    EXPECT_EQ(piece[2], Color::BLUE);
}

TEST(PieceTest, swap) {
    Piece p1 = mck::create_piece_ascending(gui::mck::from_color(gui::Color::RED));
    Piece p2 = mck::create_piece_descending(gui::mck::from_color(gui::Color::BLUE));
    const Piece p1_backup = p1;
    const Piece p2_backup = p2;

    EXPECT_EQ(p1, p1_backup) << "precondition";
    EXPECT_EQ(p2, p2_backup) << "precondition";

    p1.swap(p2);

    EXPECT_EQ(p1, p2_backup) << "there";
    EXPECT_EQ(p2, p1_backup) << "there";

    p1.swap(p2);

    EXPECT_EQ(p1, p1_backup) << "and back again";
    EXPECT_EQ(p2, p2_backup) << "and back again";
}

TEST(PieceTest, roll) {
    Piece p(mck::create_piece_ascending(0));
    std::vector<unsigned char> colors;
    for (unsigned char i = 0; i < PIECE_SIZE; ++i) {
        colors.push_back(i);
    }

    for (unsigned char i = 0; i < PIECE_SIZE; ++i) {
        const Color color = gui::mck::to_color(colors[i]);
        EXPECT_EQ(p[i], color);
    }

    p.roll_down();
    for (unsigned char i = PIECE_SIZE - 1; i > 0; --i) { // rolling down
        std::swap(colors[i], colors[i - 1]);
    }
    for (unsigned char i = 0; i < PIECE_SIZE; ++i) {
        const Color color = gui::mck::to_color(colors[i]);
        EXPECT_EQ(p[i], color);
    }

    p.roll_down();
    for (unsigned char i = PIECE_SIZE - 1; i > 0; --i) { // rolling down
        std::swap(colors[i], colors[i - 1]);
    }
    for (unsigned char i = 0; i < PIECE_SIZE; ++i) {
        const Color color = gui::mck::to_color(colors[i]);
        EXPECT_EQ(p[i], color);
    }

    p.roll_up();
    for (unsigned char i = 1; i < PIECE_SIZE; ++i) { // rolling up
        std::swap(colors[i - 1], colors[i]);
    }
    for (unsigned char i = 0; i < PIECE_SIZE; ++i) {
        const Color color = gui::mck::to_color(colors[i]);
        EXPECT_EQ(p[i], color);
    }

    p.roll_up();

    for (unsigned char i = 1; i < PIECE_SIZE; ++i) { // rolling up
        std::swap(colors[i - 1], colors[i]);
    }
    for (unsigned char i = 0; i < PIECE_SIZE; ++i) {
        const Color color = gui::mck::to_color(colors[i]);
        EXPECT_EQ(p[i], color);
    }
}
}
}
