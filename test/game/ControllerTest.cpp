#include "ControllerTest.h"

#include "../mck/game/utilgame.h"
#include "../mck/state/utilstate.h"

namespace game {
namespace tst {
using ::testing::Return;

void ControllerTest::SetUp() {
    canvas_mock = new StrictMock<mck::CanvasMock>;
    input_reader_mock = new mck::InputReaderMock();
    InputReaderPtr input_reader(input_reader_mock);
    board = std::make_shared<piece::Board>(8, 16);

    controller.reset(new Controller(CanvasPtr(canvas_mock),
          std::move(input_reader),
          board,
          157));
}

void ControllerTest::TearDown() {
    controller.reset();
}

TEST_F(ControllerTest, initial_state) {
    const state::State expected(std::make_shared<piece::Board>(8, 16),
          state::ScoreBoard(state::Score(157)));
    EXPECT_EQ(controller->state(), expected);
}

TEST_F(ControllerTest, run_with_STOP_returns_immediately) {
    const Messages::List input = { EMessage::Stop };

    EXPECT_CALL(*input_reader_mock, should_process()).WillRepeatedly(Return(true));
    EXPECT_CALL(*input_reader_mock, get_input_()).WillRepeatedly(Return(input));

    mck::prepare_state_draw(*canvas_mock, controller->state());
    controller->run(); // does not hang
}
}
}
