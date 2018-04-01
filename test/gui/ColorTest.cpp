#include "../mck/gui/utilgui.h"

#include "gui/Color.h"

#include <gtest/gtest.h>

namespace gui {
namespace tst {

TEST(ColorTest, end_color) {
    EXPECT_EQ(::gui::mck::end_color(), static_cast<size_t>(Color::LAVENDER) + 1);
}
}
}
