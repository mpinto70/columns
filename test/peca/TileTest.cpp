#include "peca/Tile.h"

#include "../mck/peca/utilpeca.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <stdexcept>

namespace peca {
namespace tst {

using gui::Color;

TEST(TestePeca, criacao) {
    const Tile t1 = mck::criaPecaSequencialCrescente(0);
    for (unsigned char i = 0; i < TILE_SIZE; ++i) {
        Color color(i, i, i);
        EXPECT_EQ(t1[i], color);
    }
    EXPECT_THROW(t1[TILE_SIZE], std::range_error);

    const Tile t2 = mck::criaPecaSequencialDecrescente(15);
    for (unsigned char i = 0; i < TILE_SIZE; ++i) {
        Color color(15 - i, 15 - i, 15 - i);
        EXPECT_EQ(t2[i], color);
    }
    EXPECT_THROW(t2[TILE_SIZE], std::range_error);

    Tile t3(t1);
    for (unsigned char i = 0; i < TILE_SIZE; ++i) {
        Color color(i, i, i);
        EXPECT_EQ(t3[i], color);
    }
    EXPECT_THROW(t3[TILE_SIZE], std::range_error);
    EXPECT_EQ(t3, t1);

    t3 = t2;
    for (unsigned char i = 0; i < TILE_SIZE; ++i) {
        Color color(15 - i, 15 - i, 15 - i);
        EXPECT_EQ(t3[i], color);
    }
    EXPECT_THROW(t3[TILE_SIZE], std::range_error);
    EXPECT_EQ(t3, t2);

    Tile p4(t1);
    EXPECT_EQ(p4, t1);
    EXPECT_EQ(t3, t2);
}

TEST(TestePeca, rolar) {
    Tile t(mck::criaPecaSequencialCrescente(0));
    std::vector<unsigned char> colors;
    for (unsigned char i = 0; i < TILE_SIZE; ++i) {
        colors.push_back(i);
    }

    for (unsigned char i = 0; i < TILE_SIZE; ++i) {
        const Color color(colors[i], colors[i], colors[i]);
        EXPECT_EQ(t[i], color);
        const Color color0(i, i, i);
        EXPECT_EQ(t[i], color0);
    }

    t.roll_down();
    for (unsigned char i = TILE_SIZE - 1; i > 0; --i) { // rolling down
        std::swap(colors[i], colors[i - 1]);
    }
    for (unsigned char i = 0; i < TILE_SIZE; ++i) {
        const Color color(colors[i], colors[i], colors[i]);
        EXPECT_EQ(t[i], color);
    }

    t.roll_down();
    for (unsigned char i = TILE_SIZE - 1; i > 0; --i) { // rolling down
        std::swap(colors[i], colors[i - 1]);
    }
    for (unsigned char i = 0; i < TILE_SIZE; ++i) {
        const Color color(colors[i], colors[i], colors[i]);
        EXPECT_EQ(t[i], color);
    }

    t.roll_up();
    for (unsigned char i = 1; i < TILE_SIZE; ++i) { // rolling up
        std::swap(colors[i - 1], colors[i]);
    }
    for (unsigned char i = 0; i < TILE_SIZE; ++i) {
        const Color color(colors[i], colors[i], colors[i]);
        EXPECT_EQ(t[i], color);
    }

    t.roll_up();

    for (unsigned char i = 1; i < TILE_SIZE; ++i) { // rolling up
        std::swap(colors[i - 1], colors[i]);
    }
    for (unsigned char i = 0; i < TILE_SIZE; ++i) {
        const Color color(colors[i], colors[i], colors[i]);
        EXPECT_EQ(t[i], color);
        const Color color0(i, i, i);
        EXPECT_EQ(t[i], color0);
    }
}

namespace {
void check_colors(const int line,
      const Tile& p,
      const std::vector<gui::Color>& colors) {
    for (unsigned char i = 0; i < TILE_SIZE; ++i) {
        const auto& color = p[i];
        EXPECT_TRUE(std::find(colors.cbegin(), colors.cend(), color) != colors.cend()) << line;
    }
}

void check_colors(const int line,
      const std::vector<gui::Color>& colors) {
    for (unsigned char i = 0; i < 100; ++i) {
        const auto p = Tile::create(colors);
        check_colors(line, p, colors);
    }
}
}

TEST(TestePeca, create_tile) {
    std::vector<gui::Color> colors;

    colors.emplace_back(1, 2, 3);
    const auto t1 = Tile::create(colors);
    EXPECT_EQ(t1, Tile(std::vector<gui::Color>(TILE_SIZE, { 1, 2, 3 })));

    check_colors(__LINE__, colors);

    colors.emplace_back(1, 2, 3);
    EXPECT_EQ(Tile::create(colors), t1);
    check_colors(__LINE__, colors);

    colors.emplace_back(4, 5, 6);
    check_colors(__LINE__, colors);

    colors.emplace_back(10, 153, 12);
    check_colors(__LINE__, colors);
}
}
}
