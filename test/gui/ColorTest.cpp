#include "../mck/util/utiltest.h"

#include "gui/Color.h"

#include <gtest/gtest.h>

#include <utility>

namespace gui {
namespace tst {

TEST(ColorTest, comparison) {
    using namespace std::rel_ops;
    const std::vector<Color> v = {
        { 1, 2, 3 },
        { 4, 2, 3 },
        { 4, 5, 3 },
        { 4, 5, 6 }
    };
    mck::check_comparison(__FILE__, __LINE__, v);
}

TEST(ColorTest, create) {
    const Color c1(1, 2, 3);
    EXPECT_EQ(c1.R, 1);
    EXPECT_EQ(c1.G, 2);
    EXPECT_EQ(c1.B, 3);
    const Color c2(231, 222, 123);
    EXPECT_EQ(c2.R, 231);
    EXPECT_EQ(c2.G, 222);
    EXPECT_EQ(c2.B, 123);

    mck::check_assignment(__FILE__, __LINE__, c1, c2);
}

TEST(ColorTest, constants) {
    static_assert(RED == Color(0x98, 0x1b, 0x1e), "wrong RED");
    static_assert(GREEN == Color(0x2e, 0x85, 0x40), "wrong GREEN");
    static_assert(BLUE == Color(0x02, 0xbf, 0xe7), "wrong BLUE");
    static_assert(WHITE == Color(0xf1, 0xf1, 0xf1), "wrong WHITE");
    static_assert(BLACK == Color(0, 0, 0), "wrong BLACK");
}

TEST(ColorTest, darken) {
    const Color color1(20, 12, 6);
    EXPECT_EQ(darken(color1, 50), Color(10, 6, 3));
    EXPECT_EQ(darken(color1, 80), Color(4, 2, 1));
    EXPECT_EQ(darken(color1, 0), color1);
    EXPECT_EQ(darken(color1, 100), BLACK);
}
}
}
