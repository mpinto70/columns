#include "ControllerTest.h"

#include "../mck/graphics/utilgraphics.h"

namespace game {
namespace tst {
using ::graphics::WindowPtr;
using ::graphics::mck::WindowMock;
using ::testing::AtLeast;

void ControllerTest::SetUp() {
    window_mock = new StrictMock<WindowMock>("name", 125, 500);
    messages = std::make_shared<Message>();
    input_reader_mock = new mck::InputReaderMock(messages);
    InputReaderPtr input_reader(input_reader_mock);
    graphics::DrawerList drawers;
    drawers.push_back(graphics::mck::create_score_board_drawer());

    controller.reset(new Controller(WindowPtr(window_mock),
          std::move(drawers),
          std::move(input_reader),
          piece::Board(8, 16, gui::WHITE),
          157));
}

void ControllerTest::TearDown() {
    controller.reset();
    messages.reset();
}

TEST_F(ControllerTest, run_with_ESC_returns_immediately) {
    EXPECT_CALL(*window_mock, clear()).Times(1);
    ::graphics::mck::prepare_score_board_draw(*window_mock, state::ScoreBoard(state::Score(157), state::Score(0)));
    messages->add(EMessage::Stop);
    controller->run(); // does not hang
}
}
}
