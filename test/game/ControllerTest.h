#pragma once

#include "../mck/game/CanvasMock.h"
#include "../mck/game/InputReaderMock.h"

#include "game/Controller.h"
#include "game/Message.h"

#include <gtest/gtest.h>

namespace game {
namespace tst {
using ::testing::StrictMock;

class ControllerTest : public ::testing::Test {
protected:
    void SetUp() override;
    void TearDown() override;

    std::unique_ptr<Controller> controller;
    mck::InputReaderMock* input_reader_mock;
    StrictMock<mck::CanvasMock>* canvas_mock;
};
}
}
