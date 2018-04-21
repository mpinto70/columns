#pragma once

#include "../mck/game/CanvasMock.h"
#include "../mck/game/InputReaderMock.h"

#include "game/MatchController.h"
#include "game/Messages.h"

#include <gtest/gtest.h>

namespace game {
namespace tst {
using ::testing::StrictMock;

class MatchControllerTest : public ::testing::Test {
protected:
    void SetUp() override;
    void TearDown() override;

    mck::InputReaderMock* input_reader_mock;
    piece::SharedBoard board;
};
}
}
