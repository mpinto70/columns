#include "ScoreBoardDrawerTest.h"

#include "../mck/gui/utilgui.h"

namespace graphics {
namespace tst {
namespace {
constexpr uint16_t X1 = 200;
constexpr uint16_t Y1 = 120;
constexpr uint16_t X2 = 250;
constexpr uint16_t Y2 = 170;
const gui::Font TITLE_FONT("Georgia", 12);
const gui::Font SCORE_FONT("Helvetica", 10);
constexpr gui::Color BACKGROUND = gui::GRAY;
constexpr gui::Color BORDER_COLOR = gui::darken(BACKGROUND, 50);
constexpr gui::Color TITLE_COLOR = gui::YELLOW;
constexpr gui::Color SCORE_COLOR = gui::GREEN;
constexpr gui::Color RECORD_COLOR = gui::darken(SCORE_COLOR, 20);
}
using ::testing::Return;

void ScoreBoardDrawerTest::SetUp() {
    window_mock.reset(new StrictMock<mck::WindowMock>("name", 125, 500));
    const gui::Rectangle box(X1, Y1, X2, Y2);
}

void ScoreBoardDrawerTest::TearDown() {
    window_mock.reset();
}

TEST_F(ScoreBoardDrawerTest, draw) {
    EXPECT_CALL(*window_mock, fill_(X1, Y1, X2, Y2, BACKGROUND)).Times(1);
    EXPECT_CALL(*window_mock, rectangle_(X1, Y1, X2, Y2, BORDER_COLOR)).Times(1);
    EXPECT_CALL(*window_mock, write_("Score", X1 + 3, Y1 + 3, TITLE_FONT, TITLE_COLOR)).WillOnce(Return(gui::Rectangle{ 0, 1, 2, 3 }));
    EXPECT_CALL(*window_mock, write_("you", X1 + 3, Y1 + 18, SCORE_FONT, SCORE_COLOR)).WillOnce(Return(gui::Rectangle{ 0, 1, 2, 3 }));
    EXPECT_CALL(*window_mock, write_("record", X1 + 3, Y1 + 33, SCORE_FONT, RECORD_COLOR)).WillOnce(Return(gui::Rectangle{ 0, 1, 2, 3 }));
    EXPECT_CALL(*window_mock, write_("10", X1 + 25, Y1 + 18, SCORE_FONT, SCORE_COLOR)).WillOnce(Return(gui::Rectangle{ 0, 1, 2, 3 }));
    EXPECT_CALL(*window_mock, write_("150", X1 + 25, Y1 + 33, SCORE_FONT, RECORD_COLOR)).WillOnce(Return(gui::Rectangle{ 0, 1, 2, 3 }));
    ScoreBoardDrawer drawer;
    drawer.draw(window_mock, score::ScoreBoard(score::Score{ 150 }, score::Score{ 10 }));
}
}
}
