#include "ControllerTest.h"

namespace game {
namespace tst {
using ::graphics::SharedWindow;
using ::graphics::mck::WindowMock;
using ::testing::AtLeast;

void ControllerTest::SetUp() {
    window_mock.reset(new StrictMock<WindowMock>("name", 125, 500));
    messages = std::make_shared<Message>();
    EXPECT_CALL(*window_mock, clear()).Times(1);
    controller.reset(new Controller(window_mock, messages));
}

void ControllerTest::TearDown() {
    controller.reset();
    window_mock.reset();
    messages.reset();
}

TEST_F(ControllerTest, run_with_ESC_returns_immediately) {
    messages->add(EMessage::Stop);
    controller->run(); // does not hang
}
}
}
