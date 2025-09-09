#include "game/Messages.h"

#include <gtest/gtest.h>

namespace game {
namespace tst {

TEST(MessagesTest, create) {
    Messages msgs;
    EXPECT_EQ(msgs.get(), Messages::List());
}

TEST(MessagesTest, add) {
    const Messages::List expected = {
        EMessage::DropDown,
        EMessage::MoveLeft,
        EMessage::Stop,
    };

    Messages msgs;
    msgs.add(EMessage::DropDown);
    msgs.add(EMessage::MoveLeft);
    msgs.add(EMessage::Stop);

    EXPECT_EQ(msgs.get(), expected);
    // the message list is emptied when you call get
    EXPECT_EQ(msgs.get(), Messages::List());
}

TEST(MessagesTest, add_vector) {
    const Messages::List expected = {
        EMessage::DropDown,
        EMessage::MoveLeft,
        EMessage::Stop,
    };

    Messages msgs;
    msgs.add(expected);

    EXPECT_EQ(msgs.get(), expected);
    // the message list is emptied when you call get
    EXPECT_EQ(msgs.get(), Messages::List());
}

TEST(MessagesTest, clear) {
    Messages msgs;
    msgs.add(EMessage::DropDown);
    msgs.add(EMessage::MoveLeft);
    msgs.add(EMessage::Stop);

    msgs.clear();
    EXPECT_EQ(msgs.get(), Messages::List());
}
} // namespace tst
} // namespace game
