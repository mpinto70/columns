#include "InputReaderTest.h"

#include "../mck/graphics/utilgraphics.h"

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

TEST_F(InputReaderTest, interrupted_from_start) {
    EXPECT_CALL(*reader, should_process()).WillOnce(Return(false));
    reader->run();
}

TEST_F(InputReaderTest, one_loop) {
    EXPECT_CALL(*reader, should_process())
          .WillOnce(Return(true))
          .WillOnce(Return(false));
    EXPECT_CALL(*reader, get_input_())
          .WillOnce(Return(Messages::List()));
    reader->run();
}

TEST_F(InputReaderTest, two_loops) {
    EXPECT_CALL(*reader, should_process())
          .WillOnce(Return(true))
          .WillOnce(Return(true))
          .WillOnce(Return(false));
    EXPECT_CALL(*reader, get_input_())
          .WillOnce(Return(Messages::List()))
          .WillOnce(Return(Messages::List()));
    reader->run();
}

TEST_F(InputReaderTest, list_of_messages) {
    const Messages::List first = { EMessage::DropDown, EMessage::MoveLeft };
    const Messages::List second = { EMessage::RollDown, EMessage::MoveRight };
    const Messages::List expected = {
        EMessage::DropDown,
        EMessage::MoveLeft,
        EMessage::RollDown,
        EMessage::MoveRight,
    };

    EXPECT_CALL(*reader, should_process())
          .WillOnce(Return(true))
          .WillOnce(Return(true))
          .WillOnce(Return(false));
    EXPECT_CALL(*reader, get_input_())
          .WillOnce(Return(first))
          .WillOnce(Return(second));
    reader->run();
    EXPECT_EQ(reader->get_input(), expected);
}

namespace {
void run_reader(InputReader* reader) {
    reader->run();
}
}

TEST_F(InputReaderTest, run_until_stopped) {
    const Messages::List input = { EMessage::DropDown, EMessage::MoveLeft };

    EXPECT_CALL(*reader, should_process()).WillRepeatedly(Return(true));
    EXPECT_CALL(*reader, get_input_()).WillRepeatedly(Return(input));

    // run the loop in a separate thread
    EXPECT_FALSE(reader->is_running());
    std::thread t1(run_reader, reader.get());
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    EXPECT_TRUE(reader->is_running());
    reader->stop();
    t1.join();
    EXPECT_FALSE(reader->is_running());

    // now check that the messages are comprised of repeated inputs
    const auto messages = reader->get_input();
    EXPECT_GT(messages.size(), 0u);
    ASSERT_EQ(messages.size() % input.size(), 0u);
    for (size_t m = 0; m < messages.size(); m += input.size()) {
        for (size_t i = 0; i < input.size(); ++i) {
            EXPECT_EQ(messages[m + i], input[i]);
        }
    }
}
}
}
