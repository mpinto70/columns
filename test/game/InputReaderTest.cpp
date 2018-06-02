#include "InputReaderTest.h"

#include "../mck/game/utilgame.h"

#include <gmock/gmock.h>

#include <chrono>
#include <thread>

namespace game {
namespace tst {

void InputReaderTest::SetUp() {
    reader.reset(new mck::InputReaderMock);
}

void InputReaderTest::TearDown() {
    reader.reset();
}

using ::testing::Return;
using ::testing::_;

TEST_F(InputReaderTest, get_input_no_message) {
    EXPECT_EQ(reader->get_input(), Messages::List());
}

namespace {
std::string build_msg(const Messages::List& inputs) {
    std::string res;
    for (auto input : inputs) {
        res += mck::to_string(input) + " ";
    }
    return res;
}

void expect_read_input(mck::InputReaderMock* reader,
      const Messages::List& inputs) {
    const auto msg = build_msg(inputs);
    EXPECT_CALL(*reader, read_input_()).WillOnce(Return(inputs));

    reader->read_input();

    EXPECT_EQ(reader->get_input(), inputs) << msg;

    // the first call cleared the input
    EXPECT_EQ(reader->get_input(), Messages::List()) << msg;

    for (auto input : inputs) {
        EXPECT_CALL(*reader, read_input_()).WillOnce(Return(Messages::List{ input }));
        reader->read_input();
    }

    EXPECT_EQ(reader->get_input(), inputs) << msg;

    // the first call cleared the input
    EXPECT_EQ(reader->get_input(), Messages::List()) << msg;
}
}

TEST_F(InputReaderTest, get_input_with_messages) {
    expect_read_input(reader.get(), { EMessage::Stop });
    expect_read_input(reader.get(), { EMessage::MoveLeft, EMessage::DropDown });
}
}
}
