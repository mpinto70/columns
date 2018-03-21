#include "../mck/util/utiltest.h"

#include "gui/Rectangle.h"

#include <gtest/gtest.h>

namespace gui {
namespace tst {

TEST(RectangleTest, create_coordinates) {
    const Rectangle r1(1, 2, 3, 4);
    EXPECT_EQ(r1.P1(), Point(1, 2));
    EXPECT_EQ(r1.P2(), Point(3, 4));
    const Rectangle r2(4, 3, 2, 1);
    EXPECT_EQ(r2.P1(), Point(2, 1));
    EXPECT_EQ(r2.P2(), Point(4, 3));

    mck::check_assignment(__FILE__, __LINE__, r1, r2);
}

TEST(RectangleTest, create_points) {
    const Rectangle r1(Point(1, 2), Point(3, 4));
    EXPECT_EQ(r1.P1(), Point(1, 2));
    EXPECT_EQ(r1.P2(), Point(3, 4));
    const Rectangle r2(Point(4, 3), Point(2, 1));
    EXPECT_EQ(r2.P1(), Point(2, 1));
    EXPECT_EQ(r2.P2(), Point(4, 3));

    mck::check_assignment(__FILE__, __LINE__, r1, r2);
}

TEST(RectangleTest, comparison) {
    const std::vector<Rectangle> v = {
        { 1, 2, 3, 4 },
        { 2, 2, 3, 4 },
        { 1, 3, 3, 4 },
        { 1, 2, 4, 4 },
        { 1, 2, 3, 5 },
    };
    mck::check_comparison(__FILE__, __LINE__, v);

    static_assert(Rectangle(1, 2, 3, 4) == Rectangle(1, 2, 3, 4), "Seriously");
    static_assert(Rectangle(2, 2, 3, 4) != Rectangle(1, 2, 3, 4), "Seriously");
    static_assert(Rectangle(1, 3, 3, 4) != Rectangle(1, 2, 3, 4), "Seriously");
    static_assert(Rectangle(1, 2, 4, 4) != Rectangle(1, 2, 3, 4), "Seriously");
    static_assert(Rectangle(1, 2, 3, 5) != Rectangle(1, 2, 3, 4), "Seriously");
}
}
}
