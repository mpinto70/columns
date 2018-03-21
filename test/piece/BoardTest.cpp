#include "../mck/piece/utilpiece.h"
#include "../mck/util/utiltest.h"

#include "piece/Board.h"

#include <gtest/gtest.h>

#include <stdexcept>
#include <utility>

namespace piece {
namespace tst {
namespace {

static void check_empty_board(const std::string& msg,
      uint16_t w,
      uint16_t h,
      const gui::Color& color) {
    EXPECT_TRUE(w > 0) << msg;
    EXPECT_TRUE(h > 0) << msg;
    const Board board(w, h, color);
    EXPECT_EQ(board.width(), w) << msg;
    EXPECT_EQ(board.height(), h) << msg;
    EXPECT_EQ(board.background_color(), color) << msg;

    for (uint16_t i = 0; i < w; ++i) {
        for (uint16_t j = 0; j < h; ++j) {
            EXPECT_EQ(board.at(i, j), color) << msg;
        }
    }

    EXPECT_THROW(board.at(w, 0), std::invalid_argument) << msg;
    EXPECT_THROW(board.at(0, h), std::invalid_argument) << msg;
}

} // unnamed namespace

TEST(BoardTest, create) {
    check_empty_board("b1", 10, 20, gui::WHITE);
    check_empty_board("b2", 15, 50, gui::RED);
    check_empty_board("b3", 7, 10, gui::BLACK);
}

TEST(BoardTest, copy) {
    const Board white(12, 25, gui::WHITE);
    Board copy(white);
    EXPECT_EQ(white, copy);

    const Board black(12, 25, gui::BLACK);
    EXPECT_NE(black, copy);

    copy = black;
    EXPECT_EQ(black, copy);
    EXPECT_NE(black, white);
}

TEST(BoardTest, invalid_create) {
    EXPECT_NO_THROW(Board(10, 20, gui::WHITE));
    uint16_t i;
    for (i = 0; i < PIECE_SIZE; ++i) {
        EXPECT_THROW(Board(i, 2 * PIECE_SIZE, gui::WHITE), std::invalid_argument) << i;
    }
    EXPECT_NO_THROW(Board(i, 20, gui::WHITE));
    for (i = 0; i < 2 * PIECE_SIZE; ++i) {
        EXPECT_THROW(Board(10, i, gui::WHITE), std::invalid_argument) << i;
    }
    EXPECT_NO_THROW(Board(PIECE_SIZE, i, gui::WHITE));
}

TEST(BoardTest, change) {
    const uint16_t WIDTH = 35;
    const uint16_t HEIGHT = 36;

    Board board(WIDTH, HEIGHT, gui::WHITE);
    EXPECT_EQ(board.background_color(), gui::WHITE);
    EXPECT_EQ(board.width(), WIDTH);
    EXPECT_EQ(board.height(), HEIGHT);

    for (uint16_t i = 0; i < WIDTH; ++i) {
        for (uint16_t j = 0; j < HEIGHT; ++j) {
            for (uint16_t ii = 0; ii < i; ++ii) {
                // previous columns are colored
                for (uint16_t jj = 0; jj < HEIGHT; ++jj) {
                    const gui::Color color(ii, jj, 0);
                    EXPECT_EQ(board.at(ii, jj), color);
                }
            }
            for (uint16_t jj = 0; jj < HEIGHT; ++jj) { // at current column
                if (jj < j) {                          // rows below j are colored
                    const gui::Color color(i, jj, 0);
                    EXPECT_EQ(board.at(i, jj), color);
                } else { // the other that are still white
                    EXPECT_EQ(board.at(i, jj), gui::WHITE);
                }
            }
            for (uint16_t ii = i + 1; ii < WIDTH; ++ii) { // the next columns are whit
                for (uint16_t jj = 0; jj < HEIGHT; ++jj) {
                    EXPECT_EQ(board.at(ii, jj), gui::WHITE);
                }
            }

            // change tile color
            const gui::Color color(i, j, 0);
            board.at(i, j) = color;
        }
    }

    EXPECT_EQ(board.background_color(), gui::WHITE);
    EXPECT_EQ(board.width(), WIDTH);
    EXPECT_EQ(board.height(), HEIGHT);
}

TEST(BoardTest, compare) {
    const std::vector<Board> vec = {
        Board(10, 20, gui::WHITE),
        Board(11, 20, gui::WHITE),
        Board(11, 21, gui::WHITE),
        Board(11, 21, gui::BLUE),
    };

    ::mck::check_comparison(__FILE__, __LINE__, vec);

    const Board tab0(10, 20, gui::BLACK);
    Board tab1(10, 20, gui::BLACK);
    for (uint16_t i = 0; i < 10; ++i) {
        for (uint16_t j = 0; j < 10; ++j) {
            EXPECT_EQ(tab0, tab1);
            tab1.at(i, j) = gui::GREEN;
            EXPECT_NE(tab0, tab1);
            tab1.at(i, j) = gui::BLACK;
            EXPECT_EQ(tab0, tab1);
        }
    }
}

TEST(BoardTest, remove) {
    const uint16_t columns = 5;
    const uint16_t rows = 7;
    std::vector<gui::Color> tiles(columns * rows, gui::BLACK);
    Board board(columns, rows, gui::BLACK);

    EXPECT_EQ(board.tiles(), tiles);

    for (uint16_t i = 0; i < columns; ++i) {
        for (uint16_t j = 0; j < rows; ++j) {
            const gui::Color color(i + 1, j + 1, 0);
            tiles.at(j * columns + i) = board.at(i, j) = color;
        }
    }

    EXPECT_EQ(board.tiles(), tiles);

    // cr = column to remove
    for (uint16_t cr = 0; cr < columns; ++cr) {
        board.remove(cr, 4);
        for (uint16_t rr = 4; rr > 0; --rr) {
            tiles.at(rr * columns + cr) = tiles.at((rr - 1) * columns + cr);
        }
        tiles.at(0 * columns + cr) = gui::BLACK;
        EXPECT_EQ(board.tiles(), tiles);
    }

    for (uint16_t i = 0; i < columns; ++i) {
        for (uint16_t j = 0; j < rows; ++j) {
            const gui::Color color(i + 1, j + 1, 0);
            tiles.at(j * columns + i) = board.at(i, j) = color;
        }
    }

    for (uint16_t rr = rows - 1; rr > 0; --rr) {
        for (uint16_t cr = 0; cr < columns; ++cr) {
            board.remove(cr, rr);
            for (uint16_t LE = rr; LE > 0; --LE) {
                tiles.at(LE * columns + cr) = tiles.at((LE - 1) * columns + cr);
            }
            tiles.at(0 * columns + cr) = gui::BLACK;
            EXPECT_EQ(board.tiles(), tiles);
        }
    }
}
}
}
