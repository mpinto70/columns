#include "InputReaderTest.h"

#include "../mck/graphics/utilgraphics.h"

#include <gmock/gmock.h>

namespace game {
namespace tst {

void InputReaderTest::SetUp() {
    messages = std::make_shared<Message>();
    reader.reset(new mck::InputReaderMock(messages));
}

void InputReaderTest::TearDown() {
    reader.reset();
    messages.reset();
}

using ::testing::Return;
using ::testing::_;

TEST_F(InputReaderTest, interrupted_from_start) {
    EXPECT_CALL(*reader, should_process()).WillOnce(Return(false));
    reader->run();
}

TEST_F(InputReaderTest, one_loop) {
    EXPECT_CALL(*reader, should_process())
          .WillOnce(Return(true))
          .WillOnce(Return(false));
    EXPECT_CALL(*reader, get_input())
          .WillOnce(Return(Message::List()));
    reader->run();
}

TEST_F(InputReaderTest, two_loops) {
    EXPECT_CALL(*reader, should_process())
          .WillOnce(Return(true))
          .WillOnce(Return(true))
          .WillOnce(Return(false));
    EXPECT_CALL(*reader, get_input())
          .WillOnce(Return(Message::List()))
          .WillOnce(Return(Message::List()));
    reader->run();
}

TEST_F(InputReaderTest, list_of_messages) {
    const Message::List first = { EMessage::MoveDown, EMessage::MoveLeft };
    const Message::List second = { EMessage::RollDown, EMessage::MoveRight };
    const Message::List expected = {
        EMessage::MoveDown,
        EMessage::MoveLeft,
        EMessage::RollDown,
        EMessage::MoveRight,
    };

    EXPECT_CALL(*reader, should_process())
          .WillOnce(Return(true))
          .WillOnce(Return(true))
          .WillOnce(Return(false));
    EXPECT_CALL(*reader, get_input())
          .WillOnce(Return(first))
          .WillOnce(Return(second));
    reader->run();
    EXPECT_EQ(messages->get(), expected);
}
}
}
