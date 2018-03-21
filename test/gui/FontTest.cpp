#include "../mck/gui/utilgui.h"
#include "../mck/util/utiltest.h"

#include "gui/Font.h"

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

    ::mck::check_assignment(__FILE__, __LINE__, f1, f2);
}

}
}
