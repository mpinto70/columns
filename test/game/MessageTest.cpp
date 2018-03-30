#include "game/Message.h"

#include <gtest/gtest.h>

namespace game {
namespace tst {

TEST(MessageTest, create) {
    Message msg;
    EXPECT_EQ(msg.get(), Message::List());
}

TEST(MessageTest, add) {
    const Message::List expected = {
        EMessage::MoveDown,
        EMessage::MoveLeft,
        EMessage::Stop,
    };

    Message msg;
    msg.add(EMessage::MoveDown);
    msg.add(EMessage::MoveLeft);
    msg.add(EMessage::Stop);

    EXPECT_EQ(msg.get(), expected);
    // the message list is emptied when you call get
    EXPECT_EQ(msg.get(), Message::List());
}

TEST(MessageTest, add_vector) {
    const Message::List expected = {
        EMessage::MoveDown,
        EMessage::MoveLeft,
        EMessage::Stop,
    };

    Message msg;
    msg.add(expected);

    EXPECT_EQ(msg.get(), expected);
    // the message list is emptied when you call get
    EXPECT_EQ(msg.get(), Message::List());
}

TEST(MessageTest, clear) {
    Message msg;
    msg.add(EMessage::MoveDown);
    msg.add(EMessage::MoveLeft);
    msg.add(EMessage::Stop);

    msg.clear();
    EXPECT_EQ(msg.get(), Message::List());
}
}
}
