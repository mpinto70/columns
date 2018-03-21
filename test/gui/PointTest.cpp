#include "../mck/util/utiltest.h"

#include "gui/Point.h"

#include <gtest/gtest.h>

namespace gui {
namespace tst {

TEST(PointTest, create) {
    const Point p1(1, 2);
    EXPECT_EQ(p1.X, 1);
    EXPECT_EQ(p1.Y, 2);
    const Point p2(231, 222);
    EXPECT_EQ(p2.X, 231);
    EXPECT_EQ(p2.Y, 222);

    mck::check_assignment(__FILE__, __LINE__, p1, p2);
}

TEST(PointTest, comparison) {
    const std::vector<Point> v = {
        { 1, 2 },
        { 4, 2 },
        { 1, 3 },
    };
    mck::check_comparison(__FILE__, __LINE__, v);

    static_assert(Point(1, 2) == Point(1, 2), "Seriously");
    static_assert(Point(2, 1) == Point(2, 1), "Seriously");
    static_assert(Point(1, 2) != Point(1, 3), "Seriously");
    static_assert(Point(1, 2) != Point(3, 2), "Seriously");
    static_assert(Point(1, 2) != Point(3, 3), "Seriously");
}
}
}
