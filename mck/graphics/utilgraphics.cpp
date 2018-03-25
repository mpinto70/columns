#include "utilgraphics.h"

#include "WindowMock.h"

#include "graphics/ScoreBoardDrawer.h"
#include "state/State.h"

#include "../mck/gui/utilgui.h"

#include <string>

namespace graphics {
namespace mck {

namespace {
constexpr gui::Rectangle BOX{ 200, 120, 250, 170 };
const gui::Font TITLE_FONT("Georgia", 12);
const gui::Font SCORE_FONT("Helvetica", 10);
constexpr gui::Color BACKGROUND = gui::GRAY;
constexpr gui::Color TITLE_COLOR = gui::YELLOW;
constexpr gui::Color SCORE_COLOR = gui::GREEN;
}

ScoreBoardDrawer create_score_board_drawer() {
    return ScoreBoardDrawer(BOX, TITLE_FONT, SCORE_FONT, BACKGROUND, TITLE_COLOR, SCORE_COLOR);
}

void prepare_score_board_draw(const ScoreBoardDrawer& drawer,
      ::testing::StrictMock<WindowMock>& window_mock,
      const state::ScoreBoard& score_board) {
    using ::testing::Return;

    const uint16_t X1 = drawer.box().P1().X;
    const uint16_t Y1 = drawer.box().P1().Y;
    const uint16_t X2 = drawer.box().P2().X;
    const uint16_t Y2 = drawer.box().P2().Y;
    const gui::Font TITLE_FONT = drawer.title_font();
    const gui::Font SCORE_FONT = drawer.score_font();
    const gui::Color BACKGROUND = drawer.background();
    const gui::Color BORDER_COLOR = drawer.border_color();
    const gui::Color TITLE_COLOR = drawer.title_color();
    const gui::Color SCORE_COLOR = drawer.score_color();
    const gui::Color RECORD_COLOR = drawer.record_color();

    const std::string score = std::to_string(score_board.score().total());
    const std::string record = std::to_string(score_board.record().total());
    EXPECT_CALL(window_mock, fill_(X1, Y1, X2, Y2, BACKGROUND)).Times(1);
    EXPECT_CALL(window_mock, rectangle_(X1, Y1, X2, Y2, BORDER_COLOR)).Times(1);
    EXPECT_CALL(window_mock, write_("Score", X1 + 3, Y1 + 3, TITLE_FONT, TITLE_COLOR)).WillOnce(Return(gui::Rectangle{ 0, 1, 2, 3 }));
    EXPECT_CALL(window_mock, write_("you", X1 + 3, Y1 + 18, SCORE_FONT, SCORE_COLOR)).WillOnce(Return(gui::Rectangle{ 0, 1, 2, 3 }));
    EXPECT_CALL(window_mock, write_("record", X1 + 3, Y1 + 33, SCORE_FONT, RECORD_COLOR)).WillOnce(Return(gui::Rectangle{ 0, 1, 2, 3 }));
    EXPECT_CALL(window_mock, write_(score, X1 + 25, Y1 + 18, SCORE_FONT, SCORE_COLOR)).WillOnce(Return(gui::Rectangle{ 0, 1, 2, 3 }));
    EXPECT_CALL(window_mock, write_(record, X1 + 25, Y1 + 33, SCORE_FONT, RECORD_COLOR)).WillOnce(Return(gui::Rectangle{ 0, 1, 2, 3 }));
}

namespace {
constexpr gui::Point TOP_LEFT{ 3, 20 };
constexpr uint16_t TILE_SIZE = 12;
constexpr uint16_t STEP_SIZE = 3;
}

void prepare_board_draw(const BoardDrawer& drawer,
      ::testing::StrictMock<mck::WindowMock>& window_mock,
      const state::State& state,
      const gui::Color& elimination_color) {
    constexpr uint16_t X1 = TOP_LEFT.X;
    constexpr uint16_t Y1 = TOP_LEFT.Y;
    const auto& board = state.board();
    const uint16_t X2 = TOP_LEFT.X + board.width() * TILE_SIZE;
    const uint16_t Y2 = TOP_LEFT.Y + board.height() * TILE_SIZE;
    const auto background = state.board().background_color();
    EXPECT_CALL(window_mock, fill_(X1, Y1, X2, Y2, background)).Times(1);
    for (size_t i = 0; i < board.width(); ++i) {
        for (size_t j = 0; j < board.height(); ++j) {
            const auto& color = board.at(i, j);
            if (color == board.background_color())
                continue;
            const auto border_color = gui::darken(color, 20);
            const uint16_t x1 = X1 + i * TILE_SIZE;
            const uint16_t y1 = Y1 + j * TILE_SIZE;
            const uint16_t x2 = x1 + TILE_SIZE - 1;
            const uint16_t y2 = y1 + TILE_SIZE - 1;
            EXPECT_CALL(window_mock, fill_(x1, y1, x2, y2, color)).Times(1);
            EXPECT_CALL(window_mock, rectangle_(x1, y1, x2, y2, border_color)).Times(1);
        }
    }
}

BoardDrawer create_board_drawer() {
    return BoardDrawer(TOP_LEFT, TILE_SIZE, STEP_SIZE);
}
}
}
