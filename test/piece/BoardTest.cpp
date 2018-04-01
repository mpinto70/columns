#include "../mck/gui/utilgui.h"
#include "../mck/piece/utilpiece.h"
#include "../mck/util/utiltest.h"

#include "piece/Board.h"

#include <gtest/gtest.h>

#include <stdexcept>
#include <utility>

namespace piece {
namespace tst {

TEST(BoardTest, caracteristics) {
    EXPECT_FALSE(std::is_move_assignable<Board>::value);
    EXPECT_FALSE(std::is_move_constructible<Board>::value);
    EXPECT_FALSE(std::is_copy_assignable<Board>::value);
    EXPECT_FALSE(std::is_copy_constructible<Board>::value);
}

namespace {

static void check_empty_board(const std::string& msg,
      size_t w,
      size_t h,
      gui::Color color) {
    EXPECT_TRUE(w > 0) << msg;
    EXPECT_TRUE(h > 0) << msg;
    const Board board(w, h, color);
    EXPECT_EQ(board.width(), w) << msg;
    EXPECT_EQ(board.height(), h) << msg;
    EXPECT_EQ(board.background_color(), color) << msg;

    for (size_t i = 0; i < w; ++i) {
        for (size_t j = 0; j < h; ++j) {
            EXPECT_EQ(board.at(i, j), color) << msg;
        }
    }

    EXPECT_THROW(board.at(w, 0), std::invalid_argument) << msg;
    EXPECT_THROW(board.at(0, h), std::invalid_argument) << msg;
}

} // unnamed namespace

TEST(BoardTest, create) {
    check_empty_board("b1", 10, 20, gui::Color::WHITE);
    check_empty_board("b2", 15, 50, gui::Color::RED);
    check_empty_board("b3", 7, 10, gui::Color::BLACK);
}

TEST(BoardTest, invalid_create) {
    EXPECT_NO_THROW(Board(10, 20, gui::Color::WHITE));
    size_t i;
    for (i = 0; i < PIECE_SIZE; ++i) {
        EXPECT_THROW(Board(i, 2 * PIECE_SIZE, gui::Color::WHITE), std::invalid_argument) << i;
    }
    EXPECT_NO_THROW(Board(i, 20, gui::Color::WHITE));
    for (i = 0; i < 2 * PIECE_SIZE; ++i) {
        EXPECT_THROW(Board(10, i, gui::Color::WHITE), std::invalid_argument) << i;
    }
    EXPECT_NO_THROW(Board(PIECE_SIZE, i, gui::Color::WHITE));
}

namespace {
void check_one_tile_colored(const Board& board,
      size_t column,
      size_t line,
      gui::Color color) {
    const std::string msg = "column=" + std::to_string(column)
                            + " / line=" + std::to_string(line)
                            + " / color=" + gui::mck::to_string(color)
                            + " / background=" + gui::mck::to_string(board.background_color());
    for (size_t i = 0; i < board.width(); ++i) {
        for (size_t j = 0; j < board.height(); ++j) {
            if (i == column && j == line) {
                EXPECT_EQ(board.at(i, j), color) << msg;
            } else {
                EXPECT_EQ(board.at(i, j), board.background_color()) << msg;
            }
        }
    }
}
}

TEST(BoardTest, change) {
    const size_t WIDTH = 35;
    const size_t HEIGHT = 36;

    Board board(WIDTH, HEIGHT, gui::Color::WHITE);
    EXPECT_EQ(board.background_color(), gui::Color::WHITE);
    EXPECT_EQ(board.width(), WIDTH);
    EXPECT_EQ(board.height(), HEIGHT);

    for (size_t i = 0; i < WIDTH; ++i) {
        for (size_t j = 0; j < HEIGHT; ++j) {
            EXPECT_EQ(board.at(i, j), gui::Color::WHITE);
            const gui::Color color = ::gui::mck::to_normalized_color(i * WIDTH + j);
            board.at(i, j) = color;
            check_one_tile_colored(board, i, j, color);
            board.at(i, j) = gui::Color::WHITE;
        }
    }
    EXPECT_EQ(board.background_color(), gui::Color::WHITE);
    EXPECT_EQ(board.width(), WIDTH);
    EXPECT_EQ(board.height(), HEIGHT);
}

TEST(BoardTest, compare) {
    std::vector<SharedConstBoard> vec;
    vec.push_back(std::make_shared<Board>(10, 20, gui::Color::WHITE));
    vec.push_back(std::make_shared<Board>(11, 20, gui::Color::WHITE));
    vec.push_back(std::make_shared<Board>(11, 21, gui::Color::WHITE));
    vec.push_back(std::make_shared<Board>(11, 21, gui::Color::BLUE));

    ::mck::check_comparison(__FILE__, __LINE__, vec);

    const Board tab0(10, 20, gui::Color::BLACK);
    Board tab1(10, 20, gui::Color::BLACK);
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 10; ++j) {
            EXPECT_EQ(tab0, tab1);
            tab1.at(i, j) = gui::Color::GREEN;
            EXPECT_NE(tab0, tab1);
            tab1.at(i, j) = gui::Color::BLACK;
            EXPECT_EQ(tab0, tab1);
        }
    }
}

TEST(BoardTest, remove) {
    const size_t columns = piece::PIECE_SIZE + 2;
    const size_t rows = 2 * piece::PIECE_SIZE + 1;
    std::vector<gui::Color> tiles(columns * rows, gui::Color::BLACK);
    Board board(columns, rows, gui::Color::BLACK);

    EXPECT_EQ(board.tiles(), tiles);

    for (size_t i = 0; i < columns; ++i) {
        for (size_t j = 0; j < rows; ++j) {
            tiles.at(j * columns + i) = board.at(i, j) = gui::Color::BLUE;
        }
    }

    EXPECT_EQ(board.tiles(), tiles);

    // cr = column to remove
    for (size_t cr = 0; cr < columns; ++cr) {
        board.remove(cr, 4);
        for (size_t rr = 4; rr > 0; --rr) {
            tiles.at(rr * columns + cr) = tiles.at((rr - 1) * columns + cr);
        }
        tiles.at(0 * columns + cr) = gui::Color::BLACK;
        EXPECT_EQ(board.tiles(), tiles);
    }

    for (size_t i = 0; i < columns; ++i) {
        for (size_t j = 0; j < rows; ++j) {
            tiles.at(j * columns + i) = board.at(i, j) = gui::Color::BLUE;
        }
    }

    for (size_t rr = rows - 1; rr > 0; --rr) {
        for (size_t cr = 0; cr < columns; ++cr) {
            board.remove(cr, rr);
            for (size_t LE = rr; LE > 0; --LE) {
                tiles.at(LE * columns + cr) = tiles.at((LE - 1) * columns + cr);
            }
            tiles.at(0 * columns + cr) = gui::Color::BLACK;
            EXPECT_EQ(board.tiles(), tiles);
        }
    }
}

TEST(BoardTest, shared_const) {
    SharedBoard board1 = std::make_shared<Board>(8, 16, gui::Color::WHITE);
    SharedConstBoard board2 = board1;
    EXPECT_EQ(board1.get(), board2.get());
}
}
}
