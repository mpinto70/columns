#include "../mck/piece/utilpiece.h"
#include "../mck/util/utiltest.h"
#include "piece/Position.h"

#include <gtest/gtest.h>

#include <stdexcept>

namespace piece {
namespace tst {

TEST(PositionTest, create) {
    const Position p1(5);
    EXPECT_EQ(p1.column(), 5u);
    EXPECT_EQ(p1.row(), 0u);
    EXPECT_EQ(p1.sub_row(), 0u);

    const Position p2(3);
    EXPECT_EQ(p2.column(), 3u);
    EXPECT_EQ(p2.row(), 0u);
    EXPECT_EQ(p2.sub_row(), 0u);

    ::mck::check_assignment(__FILE__, __LINE__, p1, p2);
}

TEST(PositionTest, step_down) {
    Position p(5);
    EXPECT_EQ(p.column(), 5u);
    EXPECT_EQ(p.row(), 0u);
    EXPECT_EQ(p.sub_row(), 0u);

    p.step_down();

    EXPECT_EQ(p.column(), 5u);
    EXPECT_EQ(p.row(), 0u);
    EXPECT_EQ(p.sub_row(), 1u);

    p.step_down();

    EXPECT_EQ(p.column(), 5u);
    EXPECT_EQ(p.row(), 0u);
    EXPECT_EQ(p.sub_row(), 2u);

    p.step_down();

    EXPECT_EQ(p.column(), 5u);
    EXPECT_EQ(p.row(), 0u);
    EXPECT_EQ(p.sub_row(), 3u);

    p.step_down();

    EXPECT_EQ(p.column(), 5u);
    EXPECT_EQ(p.row(), 0u);
    EXPECT_EQ(p.sub_row(), 4u);

    p.step_down();

    EXPECT_EQ(p.column(), 5u);
    EXPECT_EQ(p.row(), 1u);
    EXPECT_EQ(p.sub_row(), 0u);

    p.step_down();

    EXPECT_EQ(p.column(), 5u);
    EXPECT_EQ(p.row(), 1u);
    EXPECT_EQ(p.sub_row(), 1u);
}

TEST(PositionTest, move) {
    Position p(3);
    EXPECT_EQ(p.column(), 3u);
    EXPECT_EQ(p.row(), 0u);
    EXPECT_EQ(p.sub_row(), 0u);

    p.move_right();

    EXPECT_EQ(p.column(), 4u);
    EXPECT_EQ(p.row(), 0u);
    EXPECT_EQ(p.sub_row(), 0u);

    p.move_right();

    EXPECT_EQ(p.column(), 5u);
    EXPECT_EQ(p.row(), 0u);
    EXPECT_EQ(p.sub_row(), 0u);

    p.move_left();

    EXPECT_EQ(p.column(), 4u);
    EXPECT_EQ(p.row(), 0u);
    EXPECT_EQ(p.sub_row(), 0u);

    p.move_left();

    EXPECT_EQ(p.column(), 3u);
    EXPECT_EQ(p.row(), 0u);
    EXPECT_EQ(p.sub_row(), 0u);
}

TEST(PositionTest, comparison) {
    std::vector<Position> posics{
        Position(4),
        Position(5),
        Position(5),
    };

    posics.back().step_down();

    ::mck::check_comparison(__FILE__, __LINE__, posics);
}
} // namespace tst
} // namespace piece
