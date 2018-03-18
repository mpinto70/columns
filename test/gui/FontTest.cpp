#include "gui/Font.h"

#include "../mck/util/utiltst.h"

#include <gtest/gtest.h>

#include <utility>

namespace gui {
namespace tst {

TEST(FontTest, create) {
    const Font f1("font 1", 1);
    EXPECT_EQ(f1.name(), "font 1");
    EXPECT_EQ(f1.size(), 1);

    const Font f2("font 2", 2);
    EXPECT_EQ(f2.name(), "font 2");
    EXPECT_EQ(f2.size(), 2);

    mck::confereAtribuicao(__FILE__, __LINE__, f1, f2);
}

TEST(FontTest, OperatorIgual) {
    using namespace std::rel_ops;
    const std::vector<Font> v = {
        { "name 1", 2 },
        { "name 2", 2 },
        { "name 1", 3 }
    };
    mck::confereComparacao(__FILE__, __LINE__, v);
}
}
}
