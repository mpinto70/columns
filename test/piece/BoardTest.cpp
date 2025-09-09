#include "../mck/gui/utilgui.h"
#include "../mck/piece/utilpiece.h"
#include "../mck/util/utiltest.h"
#include "piece/Board.h"

#include <gtest/gtest.h>

#include <stdexcept>
#include <utility>

namespace piece {
namespace tst {
namespace {

static void check_empty_board(const std::string& msg, size_t w, size_t h) {
    EXPECT_TRUE(w > 0) << msg;
    EXPECT_TRUE(h > 0) << msg;
    const Board board(w, h);
    EXPECT_EQ(board.width(), w) << msg;
    EXPECT_EQ(board.height(), h) << msg;

    for (size_t i = 0; i < w; ++i) {
        for (size_t j = 0; j < h; ++j) {
            EXPECT_EQ(board.tile(i, j), gui::Color::NONE) << msg;
            EXPECT_FALSE(board.used(i, j)) << msg;
        }
    }
}

} // unnamed namespace

TEST(BoardTest, create) {
    check_empty_board("b1", 10, 20);
    check_empty_board("b2", 15, 50);
    check_empty_board("b3", 7, 10);
}

TEST(BoardTest, invalid_create) {
    EXPECT_NO_THROW(Board(10, 20));
    size_t i;
    for (i = 0; i < PIECE_SIZE; ++i) {
        EXPECT_THROW(Board(i, 2 * PIECE_SIZE), std::invalid_argument) << i;
    }
    EXPECT_NO_THROW(Board(i, 20));
    for (i = 0; i < 2 * PIECE_SIZE; ++i) {
        EXPECT_THROW(Board(10, i), std::invalid_argument) << i;
    }
    EXPECT_NO_THROW(Board(PIECE_SIZE, i));
}

namespace {
void check_one_tile_colored(const Board& board, size_t column, size_t line, gui::Color color) {
    const std::string msg = "column=" + std::to_string(column) + " / line=" + std::to_string(line)
                            + " / color=" + gui::mck::to_string(color)
                            + " / background=" + gui::mck::to_string(gui::Color::NONE);
    for (size_t i = 0; i < board.width(); ++i) {
        for (size_t j = 0; j < board.height(); ++j) {
            if (i == column && j == line) {
                EXPECT_EQ(board.tile(i, j), color) << msg;
                EXPECT_TRUE(board.used(i, j)) << msg;
            } else {
                EXPECT_EQ(board.tile(i, j), gui::Color::NONE) << msg;
                EXPECT_FALSE(board.used(i, j)) << msg;
            }
        }
    }
}
} // namespace

TEST(BoardTest, change) {
    const size_t WIDTH = 35;
    const size_t HEIGHT = 36;

    Board board(WIDTH, HEIGHT);
    EXPECT_EQ(board.width(), WIDTH);
    EXPECT_EQ(board.height(), HEIGHT);

    for (size_t i = 0; i < WIDTH; ++i) {
        for (size_t j = 0; j < HEIGHT; ++j) {
            EXPECT_EQ(board.tile(i, j), gui::Color::NONE);
            const gui::Color color = ::gui::mck::to_normalized_color(i * WIDTH + j);
            board.tile(i, j) = color;
            check_one_tile_colored(board, i, j, color);
            board.tile(i, j) = gui::Color::NONE;
        }
    }
    EXPECT_EQ(board.width(), WIDTH);
    EXPECT_EQ(board.height(), HEIGHT);
}

TEST(BoardTest, compare) {
    std::vector<SharedConstBoard> vec;
    vec.push_back(std::make_shared<Board>(10, 20));
    vec.push_back(std::make_shared<Board>(11, 20));
    vec.push_back(std::make_shared<Board>(11, 21));

    ::mck::check_comparison(__FILE__, __LINE__, vec);

    const Board tab0(10, 20);
    Board tab1(10, 20);
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 10; ++j) {
            EXPECT_EQ(tab0, tab1);
            tab1.tile(i, j) = gui::Color::GREEN;
            EXPECT_NE(tab0, tab1);
            tab1.tile(i, j) = gui::Color::NONE;
            EXPECT_EQ(tab0, tab1);
        }
    }
}

TEST(BoardTest, remove) {
    const size_t columns = piece::PIECE_SIZE + 2;
    const size_t rows = 2 * piece::PIECE_SIZE + 1;
    std::vector<gui::Color> tiles(columns * rows, gui::Color::NONE);
    Board board(columns, rows);

    EXPECT_EQ(board.tiles(), tiles);

    for (size_t i = 0; i < columns; ++i) {
        for (size_t j = 0; j < rows; ++j) {
            tiles.at(j * columns + i) = board.tile(i, j) =
                  gui::mck::to_normalized_color(j * columns + i);
        }
    }

    EXPECT_EQ(board.tiles(), tiles);

    // cr = column to remove
    for (size_t cr = 0; cr < columns; ++cr) {
        board.remove(cr, 4);
        for (size_t rr = 4; rr > 0; --rr) {
            tiles.at(rr * columns + cr) = tiles.at((rr - 1) * columns + cr);
        }
        tiles.at(0 * columns + cr) = gui::Color::NONE;
        EXPECT_EQ(board.tiles(), tiles);
    }

    for (size_t i = 0; i < columns; ++i) {
        for (size_t j = 0; j < rows; ++j) {
            tiles.at(j * columns + i) = board.tile(i, j) = gui::Color::BLUE;
        }
    }

    for (size_t rr = rows - 1; rr > 0; --rr) {
        for (size_t cr = 0; cr < columns; ++cr) {
            board.remove(cr, rr);
            for (size_t LE = rr; LE > 0; --LE) {
                tiles.at(LE * columns + cr) = tiles.at((LE - 1) * columns + cr);
            }
            tiles.at(0 * columns + cr) = gui::Color::NONE;
            EXPECT_EQ(board.tiles(), tiles);
        }
    }
}

TEST(BoardTest, remove_list) {
    const size_t columns = piece::PIECE_SIZE + 2;
    const size_t rows = 2 * piece::PIECE_SIZE + 1;
    Board board(columns, rows);
    Board expected(columns, rows);

    for (size_t i = 0; i < columns; ++i) {
        for (size_t j = 0; j < rows; ++j) {
            board.tile(i, j) = expected.tile(i, j) = gui::mck::to_normalized_color(j * columns + i);
        }
    }

    const Board::EliminationList elimination_list = {
        { columns - 1, rows - 1 },
        { 0,           rows - 1 },
        { 1,           rows - 3 },
        { columns - 2, rows - 2 },
    };

    for (const auto& elimination : elimination_list) {
        expected.remove(elimination.column, elimination.row);
    }

    board.remove(elimination_list);
    EXPECT_EQ(board, expected);
}

TEST(BoardTest, shared_const) {
    SharedBoard board1 = std::make_shared<Board>(8, 16);
    SharedConstBoard board2 = board1;
    EXPECT_EQ(board1.get(), board2.get());
}

TEST(BoardTest, elimination_list_is_empty_for_new_board) {
    const Board board(10, 20);
    EXPECT_TRUE(board.elimination_list().empty());
}

TEST(BoardTest, elimination_list_of_a_full_board_is_the_full_board) {
    Board board(10, 20);
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 20; ++j) {
            board.tile(i, j) = gui::Color::BLUE;
        }
    }
    const auto list = board.elimination_list();
    EXPECT_FALSE(list.empty());
    ASSERT_EQ(list.size(), 20u * 10u);
    for (size_t i = 0; i < 10; ++i) {
        for (size_t j = 0; j < 20; ++j) {
            const size_t index = i * 20 + j;
            const auto& tile = list.at(index);
            EXPECT_EQ(tile.column, i) << i << " / " << j << " - " << index;
            EXPECT_EQ(tile.row, j) << i << " / " << j << " - " << index;
        }
    }
}

TEST(BoardTest, elimination_list_with_three_in_horizontal) {
    Board board(10, 20);
    board.tile(0, 0) = gui::Color::BLUE;
    board.tile(1, 0) = gui::Color::BLUE;
    board.tile(2, 0) = gui::Color::BLUE;
    const auto list = board.elimination_list();
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 3u);
    const Board::EliminationList expected = {
        { 0, 0 },
        { 1, 0 },
        { 2, 0 },
    };
    EXPECT_EQ(list, expected);
}

TEST(BoardTest, elimination_list_with_four_in_horizontal) {
    Board board(10, 20);
    board.tile(0, 0) = gui::Color::RED;
    board.tile(1, 0) = gui::Color::RED;
    board.tile(2, 0) = gui::Color::RED;
    board.tile(3, 0) = gui::Color::RED;
    const auto list = board.elimination_list();
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 4u);
    const Board::EliminationList expected = {
        { 0, 0 },
        { 1, 0 },
        { 2, 0 },
        { 3, 0 },
    };
    EXPECT_EQ(list, expected);
}

TEST(BoardTest, elimination_list_with_two_horizontal_triplets) {
    Board board(10, 20);
    board.tile(0, 0) = gui::Color::RED;
    board.tile(1, 0) = gui::Color::RED;
    board.tile(2, 0) = gui::Color::RED;
    board.tile(4, 7) = gui::Color::BLUE;
    board.tile(5, 7) = gui::Color::BLUE;
    board.tile(6, 7) = gui::Color::BLUE;
    const auto list = board.elimination_list();
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 6u);
    const Board::EliminationList expected = {
        { 0, 0 },
        { 1, 0 },
        { 2, 0 },
        { 4, 7 },
        { 5, 7 },
        { 6, 7 },
    };
    EXPECT_EQ(list, expected);
}

TEST(BoardTest, elimination_list_is_empty_different_colors) {
    Board board(10, 20);
    board.tile(0, 0) = gui::Color::BLUE;
    board.tile(1, 0) = gui::Color::RED;
    board.tile(2, 0) = gui::Color::BLUE;
    const auto list = board.elimination_list();
    EXPECT_TRUE(list.empty());
}

TEST(BoardTest, elimination_list_is_empty_if_not_contiguos_horizontal) {
    Board board(10, 20);
    board.tile(0, 0) = gui::Color::BLUE;
    board.tile(2, 0) = gui::Color::BLUE;
    board.tile(3, 0) = gui::Color::BLUE;
    const auto list = board.elimination_list();
    EXPECT_TRUE(list.empty());
}

TEST(BoardTest, elimination_list_with_three_in_vertical) {
    Board board(10, 20);
    board.tile(0, 0) = gui::Color::BLUE;
    board.tile(0, 1) = gui::Color::BLUE;
    board.tile(0, 2) = gui::Color::BLUE;
    const auto list = board.elimination_list();
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 3u);
    const Board::EliminationList expected = {
        { 0, 0 },
        { 0, 1 },
        { 0, 2 },
    };
    EXPECT_EQ(list, expected);
}

TEST(BoardTest, elimination_list_with_four_in_vertical) {
    Board board(10, 20);
    board.tile(0, 0) = gui::Color::RED;
    board.tile(0, 1) = gui::Color::RED;
    board.tile(0, 2) = gui::Color::RED;
    board.tile(0, 3) = gui::Color::RED;
    const auto list = board.elimination_list();
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 4u);
    const Board::EliminationList expected = {
        { 0, 0 },
        { 0, 1 },
        { 0, 2 },
        { 0, 3 },
    };
    EXPECT_EQ(list, expected);
}

TEST(BoardTest, elimination_list_with_two_vertical_triplets) {
    Board board(10, 20);
    board.tile(0, 0) = gui::Color::RED;
    board.tile(0, 1) = gui::Color::RED;
    board.tile(0, 2) = gui::Color::RED;
    board.tile(7, 4) = gui::Color::BLUE;
    board.tile(7, 5) = gui::Color::BLUE;
    board.tile(7, 6) = gui::Color::BLUE;
    const auto list = board.elimination_list();
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 6u);
    const Board::EliminationList expected = {
        { 0, 0 },
        { 0, 1 },
        { 0, 2 },
        { 7, 4 },
        { 7, 5 },
        { 7, 6 },
    };
    EXPECT_EQ(list, expected);
}

TEST(BoardTest, elimination_list_is_empty_different_colors_vertical) {
    Board board(10, 20);
    board.tile(0, 0) = gui::Color::BLUE;
    board.tile(0, 1) = gui::Color::RED;
    board.tile(0, 2) = gui::Color::BLUE;
    const auto list = board.elimination_list();
    EXPECT_TRUE(list.empty());
}

TEST(BoardTest, elimination_list_with_three_in_diagonal_descendent) {
    Board board(10, 20);
    board.tile(0, 0) = gui::Color::BLUE;
    board.tile(1, 1) = gui::Color::BLUE;
    board.tile(2, 2) = gui::Color::BLUE;
    const auto list = board.elimination_list();
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 3u);
    const Board::EliminationList expected = {
        { 0, 0 },
        { 1, 1 },
        { 2, 2 },
    };
    EXPECT_EQ(list, expected);
}

TEST(BoardTest, elimination_list_with_four_in_diagonal_descendent) {
    Board board(10, 20);
    board.tile(0, 0) = gui::Color::BLUE;
    board.tile(1, 1) = gui::Color::BLUE;
    board.tile(2, 2) = gui::Color::BLUE;
    board.tile(3, 3) = gui::Color::BLUE;
    const auto list = board.elimination_list();
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 4u);
    const Board::EliminationList expected = {
        { 0, 0 },
        { 1, 1 },
        { 2, 2 },
        { 3, 3 },
    };
    EXPECT_EQ(list, expected);
}

TEST(BoardTest, elimination_list_with_two_triplets_in_diagonal_descendent) {
    Board board(10, 20);
    board.tile(0, 0) = gui::Color::BLUE;
    board.tile(1, 1) = gui::Color::BLUE;
    board.tile(2, 2) = gui::Color::BLUE;
    board.tile(7, 4) = gui::Color::RED;
    board.tile(8, 5) = gui::Color::RED;
    board.tile(9, 6) = gui::Color::RED;
    const auto list = board.elimination_list();
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 6u);
    const Board::EliminationList expected = {
        { 0, 0 },
        { 1, 1 },
        { 2, 2 },
        { 7, 4 },
        { 8, 5 },
        { 9, 6 },
    };
    EXPECT_EQ(list, expected);
}

TEST(BoardTest, elimination_list_is_empty_different_colors_diagonal_descendent) {
    Board board(10, 20);
    board.tile(0, 0) = gui::Color::BLUE;
    board.tile(1, 1) = gui::Color::RED;
    board.tile(2, 2) = gui::Color::BLUE;
    const auto list = board.elimination_list();
    EXPECT_TRUE(list.empty());
}

TEST(BoardTest, elimination_list_with_three_in_diagonal_ascendent) {
    Board board(10, 20);
    board.tile(7, 3) = gui::Color::BLUE;
    board.tile(8, 2) = gui::Color::BLUE;
    board.tile(9, 1) = gui::Color::BLUE;
    const auto list = board.elimination_list();
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 3u);
    const Board::EliminationList expected = {
        { 7, 3 },
        { 8, 2 },
        { 9, 1 },
    };
    EXPECT_EQ(list, expected);
}

TEST(BoardTest, elimination_list_with_four_in_diagonal_ascendent) {
    Board board(10, 20);
    board.tile(6, 3) = gui::Color::BLUE;
    board.tile(7, 2) = gui::Color::BLUE;
    board.tile(8, 1) = gui::Color::BLUE;
    board.tile(9, 0) = gui::Color::BLUE;
    const auto list = board.elimination_list();
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 4u);
    const Board::EliminationList expected = {
        { 6, 3 },
        { 7, 2 },
        { 8, 1 },
        { 9, 0 },
    };
    EXPECT_EQ(list, expected);
}

TEST(BoardTest, elimination_list_with_two_triplets_in_diagonal_ascendent) {
    Board board(10, 20);
    board.tile(7, 3) = gui::Color::BLUE;
    board.tile(8, 2) = gui::Color::BLUE;
    board.tile(9, 1) = gui::Color::BLUE;
    board.tile(3, 7) = gui::Color::RED;
    board.tile(4, 6) = gui::Color::RED;
    board.tile(5, 5) = gui::Color::RED;
    const auto list = board.elimination_list();
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 6u);
    const Board::EliminationList expected = {
        { 3, 7 },
        { 4, 6 },
        { 5, 5 },
        { 7, 3 },
        { 8, 2 },
        { 9, 1 },
    };
    EXPECT_EQ(list, expected);
}

/*
 *    __________
 *  0|          |
 *  1|          |
 *  2|          |
 *  3|          |
 *  4|          |
 *  5|          |
 *  6|          |
 *  7|          |
 *  8|          |
 *  9|          |
 * 10|          |
 * 11| b b      |
 * 12| rby  g   |
 * 13|ybrby g   |
 * 14|byyrrrggg |
 *    ----------
 *    0123456789
 */
TEST(BoardTest, elimination_list_multiple_directions) {
    Board board(10, 15);
    board.tile(1, 11) = gui::Color::BLUE;
    board.tile(3, 11) = gui::Color::BLUE;
    board.tile(1, 12) = gui::Color::RED;
    board.tile(2, 12) = gui::Color::BLUE;
    board.tile(3, 12) = gui::Color::YELLOW;
    board.tile(6, 12) = gui::Color::GREEN;
    board.tile(0, 13) = gui::Color::YELLOW;
    board.tile(1, 13) = gui::Color::BLUE;
    board.tile(2, 13) = gui::Color::RED;
    board.tile(3, 13) = gui::Color::BLUE;
    board.tile(4, 13) = gui::Color::YELLOW;
    board.tile(6, 13) = gui::Color::GREEN;
    board.tile(0, 14) = gui::Color::BLUE;
    board.tile(1, 14) = gui::Color::YELLOW;
    board.tile(2, 14) = gui::Color::YELLOW;
    board.tile(3, 14) = gui::Color::RED;
    board.tile(4, 14) = gui::Color::RED;
    board.tile(5, 14) = gui::Color::RED;
    board.tile(6, 14) = gui::Color::GREEN;
    board.tile(7, 14) = gui::Color::GREEN;
    board.tile(8, 14) = gui::Color::GREEN;
    const auto list = board.elimination_list();
    EXPECT_FALSE(list.empty());
    const Board::EliminationList expected = {
        { 0, 14 },
        { 1, 11 },
        { 1, 12 },
        { 1, 13 },
        { 2, 12 },
        { 2, 13 },
        { 3, 11 },
        { 3, 13 },
        { 3, 14 },
        { 4, 14 },
        { 5, 14 },
        { 6, 12 },
        { 6, 13 },
        { 6, 14 },
        { 7, 14 },
        { 8, 14 },
    };
    EXPECT_EQ(list, expected);
}
} // namespace tst
} // namespace piece
