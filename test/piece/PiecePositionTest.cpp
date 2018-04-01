#include "../mck/piece/utilpiece.h"
#include "../mck/util/utiltest.h"

#include "piece/Board.h"
#include "piece/PiecePosition.h"

#include <gtest/gtest.h>

#include <stdexcept>

namespace piece {
namespace tst {

namespace {
void check_invalid_creation(const std::string& msg0, SharedConstBoard board) {
    for (size_t i = 0; i < 2 * board->width(); ++i) {
        if (i < board->width()) {
            EXPECT_NO_THROW(PiecePosition(board, i, 4)) << msg0;
        } else {
            try {
                PiecePosition p(board, i, 4);
                FAIL() << msg0;
            } catch (std::invalid_argument& e) {
                EXPECT_EQ(std::string(e.what()), "PiecePosition - column is greater than board width") << msg0;
            }
        }
    }

    EXPECT_NO_THROW(PiecePosition(board, 0, 4)) << msg0;
    try {
        PiecePosition p(board, 0, 0);
        FAIL() << msg0;
    } catch (std::invalid_argument& e) {
        EXPECT_EQ(std::string(e.what()), "PiecePosition - zero maximum subdivision") << msg0;
    }
}

void check_step_down_invalid(const std::string& msg0, SharedConstBoard board) {
    PiecePosition p(board, board->width() - 1, 7);
    while (p.row() != board->height() - PIECE_SIZE) {
        EXPECT_TRUE(not p.reached_bottom()) << msg0;
        EXPECT_NO_THROW(p.step_down()) << msg0;
    }

    EXPECT_TRUE(p.reached_bottom()) << msg0;
    EXPECT_EQ(p.row(), board->height() - PIECE_SIZE) << msg0;
    EXPECT_EQ(p.sub_row(), 0u) << msg0;

    try {
        p.step_down();
        FAIL() << msg0;
    } catch (std::logic_error& e) {
        EXPECT_EQ(std::string(e.what()), "PiecePosition::step_down - already at bottom") << msg0;
    }
}

void check_move_invalid(const std::string& msg0, SharedConstBoard board) {
    PiecePosition p(board, 0, 4);
    for (size_t i = 0; i < board->width() - 1; ++i) {
        EXPECT_EQ(p.column(), i) << msg0;
        EXPECT_EQ(p.row(), 0u) << msg0;
        EXPECT_EQ(p.sub_row(), 0u) << msg0;
        EXPECT_NO_THROW(p.move_right()) << msg0;
        EXPECT_EQ(p.column(), i + 1) << msg0;
        EXPECT_EQ(p.row(), 0u) << msg0;
        EXPECT_EQ(p.sub_row(), 0u) << msg0;
    }

    EXPECT_EQ(p.column(), board->width() - 1) << msg0;
    EXPECT_EQ(p.row(), 0u) << msg0;
    EXPECT_EQ(p.sub_row(), 0u) << msg0;
    EXPECT_THROW(p.move_right(), std::logic_error) << msg0;
    EXPECT_EQ(p.column(), board->width() - 1) << msg0;
    EXPECT_EQ(p.row(), 0u) << msg0;
    EXPECT_EQ(p.sub_row(), 0u) << msg0;

    for (size_t i = board->width(); i > 1; --i) {
        EXPECT_EQ(p.column(), i - 1) << msg0;
        EXPECT_EQ(p.row(), 0u) << msg0;
        EXPECT_EQ(p.sub_row(), 0u) << msg0;
        EXPECT_NO_THROW(p.move_left()) << msg0;
        EXPECT_EQ(p.column(), i - 2) << msg0;
        EXPECT_EQ(p.row(), 0u) << msg0;
        EXPECT_EQ(p.sub_row(), 0u) << msg0;
    }

    EXPECT_EQ(p.column(), 0u) << msg0;
    EXPECT_EQ(p.row(), 0u) << msg0;
    EXPECT_EQ(p.sub_row(), 0u) << msg0;
    EXPECT_THROW(p.move_left(), std::logic_error) << msg0;
    EXPECT_EQ(p.column(), 0u) << msg0;
    EXPECT_EQ(p.row(), 0u) << msg0;
    EXPECT_EQ(p.sub_row(), 0u) << msg0;
}
}

TEST(PiecePositionTest, create) {
    SharedConstBoard board1 = std::make_shared<const Board>(7, 25, gui::Color::WHITE);
    SharedConstBoard board2 = std::make_shared<const Board>(8, 15, gui::Color::WHITE);

    const PiecePosition p1(board1, 5, 4);
    EXPECT_EQ(p1.column(), 5u);
    EXPECT_EQ(p1.row(), 0u);
    EXPECT_EQ(p1.sub_row(), 0u);
    EXPECT_EQ(p1.max_column(), 7u);

    const PiecePosition p2(board2, 3, 4);
    EXPECT_EQ(p2.column(), 3u);
    EXPECT_EQ(p2.row(), 0u);
    EXPECT_EQ(p2.sub_row(), 0u);
    EXPECT_EQ(p2.max_column(), 8u);

    PiecePosition p3(p1);
    EXPECT_EQ(p3.column(), 5u);
    EXPECT_EQ(p3.row(), 0u);
    EXPECT_EQ(p3.sub_row(), 0u);
    EXPECT_EQ(p3.max_column(), 7u);

    p3 = p2;
    EXPECT_EQ(p3.column(), 3u);
    EXPECT_EQ(p3.row(), 0u);
    EXPECT_EQ(p3.sub_row(), 0u);
    EXPECT_EQ(p3.max_column(), 8u);
}

TEST(PiecePositionTest, invalid_create) {
    check_invalid_creation("t1", std::make_shared<Board>(7, 25, gui::Color::WHITE));
    check_invalid_creation("t2", std::make_shared<Board>(12, 50, gui::Color::WHITE));
}

TEST(PiecePositionTest, step_down) {
    SharedConstBoard board = std::make_shared<const Board>(7, 25, gui::Color::WHITE);

    PiecePosition p(board, 5, 6);
    EXPECT_EQ(p.column(), 5u);
    EXPECT_EQ(p.row(), 0u);
    EXPECT_EQ(p.sub_row(), 0u);
    EXPECT_EQ(p.max_sub_row(), 6u);

    p.step_down();

    EXPECT_EQ(p.column(), 5u);
    EXPECT_EQ(p.row(), 0u);
    EXPECT_EQ(p.sub_row(), 1u);
    EXPECT_EQ(p.max_sub_row(), 6u);

    p.step_down();

    EXPECT_EQ(p.column(), 5u);
    EXPECT_EQ(p.row(), 0u);
    EXPECT_EQ(p.sub_row(), 2u);
    EXPECT_EQ(p.max_sub_row(), 6u);

    p.step_down();

    EXPECT_EQ(p.column(), 5u);
    EXPECT_EQ(p.row(), 0u);
    EXPECT_EQ(p.sub_row(), 3u);
    EXPECT_EQ(p.max_sub_row(), 6u);

    p.step_down();

    EXPECT_EQ(p.column(), 5u);
    EXPECT_EQ(p.row(), 0u);
    EXPECT_EQ(p.sub_row(), 4u);
    EXPECT_EQ(p.max_sub_row(), 6u);

    p.step_down();

    EXPECT_EQ(p.column(), 5u);
    EXPECT_EQ(p.row(), 0u);
    EXPECT_EQ(p.sub_row(), 5u);
    EXPECT_EQ(p.max_sub_row(), 6u);

    p.step_down();

    EXPECT_EQ(p.column(), 5u);
    EXPECT_EQ(p.row(), 1u);
    EXPECT_EQ(p.sub_row(), 0u);
    EXPECT_EQ(p.max_sub_row(), 6u);

    p.step_down();

    EXPECT_EQ(p.column(), 5u);
    EXPECT_EQ(p.row(), 1u);
    EXPECT_EQ(p.sub_row(), 1u);
    EXPECT_EQ(p.max_sub_row(), 6u);
}

TEST(PiecePositionTest, invalid_step_down) {
    check_step_down_invalid("t1", std::make_shared<Board>(12, 50, gui::Color::BLACK));
    check_step_down_invalid("t2", std::make_shared<Board>(7, 25, gui::Color::BLACK));
}

TEST(PiecePositionTest, move) {
    SharedConstBoard board = std::make_shared<const Board>(7, 25, gui::Color::WHITE);

    PiecePosition p(board, 3, 4);
    EXPECT_EQ(p.column(), 3u);
    EXPECT_EQ(p.row(), 0u);
    EXPECT_EQ(p.sub_row(), 0u);
    EXPECT_EQ(p.max_sub_row(), 4u);

    p.move_right();

    EXPECT_EQ(p.column(), 4u);
    EXPECT_EQ(p.row(), 0u);
    EXPECT_EQ(p.sub_row(), 0u);
    EXPECT_EQ(p.max_sub_row(), 4u);

    p.move_right();

    EXPECT_EQ(p.column(), 5u);
    EXPECT_EQ(p.row(), 0u);
    EXPECT_EQ(p.sub_row(), 0u);
    EXPECT_EQ(p.max_sub_row(), 4u);

    p.move_left();

    EXPECT_EQ(p.column(), 4u);
    EXPECT_EQ(p.row(), 0u);
    EXPECT_EQ(p.sub_row(), 0u);
    EXPECT_EQ(p.max_sub_row(), 4u);

    p.move_left();

    EXPECT_EQ(p.column(), 3u);
    EXPECT_EQ(p.row(), 0u);
    EXPECT_EQ(p.sub_row(), 0u);
    EXPECT_EQ(p.max_sub_row(), 4u);
}

TEST(PiecePositionTest, invalid_move) {
    check_move_invalid("t1", std::make_shared<Board>(12, 50, gui::Color::BLACK));
    check_move_invalid("t2", std::make_shared<Board>(7, 25, gui::Color::BLACK));
}

TEST(PiecePositionTest, comparison) {
    SharedConstBoard t1 = std::make_shared<const Board>(12, 50, gui::Color::BLACK);

    std::vector<PiecePosition> posics{
        PiecePosition(t1, 4, 4),
        PiecePosition(t1, 5, 4),
        PiecePosition(t1, 5, 6),
        PiecePosition(t1, 5, 6),
    };

    posics.back().step_down();

    ::mck::check_comparison(__FILE__, __LINE__, posics);

    SharedConstBoard t2 = std::make_shared<const Board>(17, 50, gui::Color::WHITE);
    EXPECT_EQ(posics[0], PiecePosition(t2, 4, 4));
    EXPECT_EQ(posics[1], PiecePosition(t2, 5, 4));
}
}
}
