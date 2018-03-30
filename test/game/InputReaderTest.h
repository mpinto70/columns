#pragma once

#include "../mck/game/InputReaderMock.h"

#include "game/InputReader.h"
#include "game/Message.h"

#include <gtest/gtest.h>

namespace game {
namespace tst {
using ::testing::StrictMock;

class InputReaderTest : public ::testing::Test {
protected:
    void SetUp() override;
    void TearDown() override;

    std::unique_ptr<mck::InputReaderMock> reader;
    SharedMessage messages;
};
}
}
