#include "ControllerTest.h"

#include "../mck/game/utilgame.h"
#include "../mck/state/utilstate.h"

namespace game {
namespace tst {
using ::testing::AtLeast;

void ControllerTest::SetUp() {
    canvas_mock = new StrictMock<mck::CanvasMock>;
    messages = std::make_shared<Message>();
    input_reader_mock = new mck::InputReaderMock(messages);
    InputReaderPtr input_reader(input_reader_mock);

    controller.reset(new Controller(CanvasPtr(canvas_mock),
          std::move(input_reader),
          8,
          16,
          gui::Color::WHITE,
          157));
}

void ControllerTest::TearDown() {
    controller.reset();
    messages.reset();
}

TEST_F(ControllerTest, initial_state) {
    const state::State expected(piece::Board(8, 16, gui::Color::WHITE),
          state::ScoreBoard(state::Score(157), state::Score(0)));
    EXPECT_EQ(controller->state(), expected);
}

TEST_F(ControllerTest, run_with_ESC_returns_immediately) {
    mck::prepare_state_draw(*canvas_mock, controller->state());
    messages->add(EMessage::Stop);
    controller->run(); // does not hang
}
}
}
