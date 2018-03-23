#pragma once

#include "../mck/graphics/WindowMock.h"

#include "game/Controller.h"
#include "game/Message.h"
#include "graphics/Window.h"

#include <gtest/gtest.h>

namespace game {
namespace tst {
using ::testing::StrictMock;

class ControllerTest : public ::testing::Test {
protected:
    void SetUp() override;
    void TearDown() override;

    std::unique_ptr<Controller> controller;
    std::shared_ptr<StrictMock<graphics::mck::WindowMock>> window_mock;
    SharedMessage messages;
};
}
}
