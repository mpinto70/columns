#include "ControllerTest.h"

#include "../mck/graphics/utilgraphics.h"

namespace game {
namespace tst {
using ::graphics::SharedWindow;
using ::graphics::mck::WindowMock;
using ::testing::AtLeast;

void ControllerTest::SetUp() {
    window_mock.reset(new StrictMock<WindowMock>("name", 125, 500));
    messages = std::make_shared<Message>();
    EXPECT_CALL(*window_mock, clear()).Times(1);
    score_board_drawer.reset(new graphics::ScoreBoardDrawer(::graphics::mck::create_score_board_drawer()));
    ::graphics::mck::prepare_score_board_draw(*score_board_drawer, *window_mock, state::ScoreBoard());
    controller.reset(new Controller(window_mock, *score_board_drawer, messages));
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
