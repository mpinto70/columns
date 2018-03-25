#pragma once

#include "../mck/graphics/WindowMock.h"

#include <gtest/gtest.h>

namespace graphics {
namespace tst {
using ::testing::StrictMock;

class BoardDrawerTest : public ::testing::Test {
protected:
    void SetUp() override;
    void TearDown() override;

    std::shared_ptr<StrictMock<mck::WindowMock>> window_mock;
};
}
}
