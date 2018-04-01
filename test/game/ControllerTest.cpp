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
}
}
