#include "ScoreBoardDrawer.h"

namespace graphics {
constexpr gui::Rectangle BOX{ 200, 120, 250, 170 };
const gui::Font TITLE_FONT("Georgia", 12);
const gui::Font SCORE_FONT("Helvetica", 10);
constexpr gui::Color BACKGROUND = gui::GRAY;
constexpr gui::Color BORDER_COLOR = gui::darken(BACKGROUND, 50);
constexpr gui::Color TITLE_COLOR = gui::YELLOW;
constexpr gui::Color SCORE_COLOR = gui::GREEN;
constexpr gui::Color RECORD_COLOR = gui::darken(SCORE_COLOR, 20);

void ScoreBoardDrawer::draw(SharedWindow window, const score::ScoreBoard& score_board) const {
    window->fill(BOX, BACKGROUND);
    window->rectangle(BOX, BORDER_COLOR);
    window->write("Score", BOX.P1() + gui::Point{ 3, 3 }, TITLE_FONT, TITLE_COLOR);
    window->write("you", BOX.P1() + gui::Point{ 3, 18 }, SCORE_FONT, SCORE_COLOR);
    window->write("record", BOX.P1() + gui::Point{ 3, 33 }, SCORE_FONT, RECORD_COLOR);
    window->write(std::to_string(score_board.score().total()), BOX.P1() + gui::Point{ 25, 18 }, SCORE_FONT, SCORE_COLOR);
    window->write(std::to_string(score_board.record().total()), BOX.P1() + gui::Point{ 25, 33 }, SCORE_FONT, RECORD_COLOR);
}
}
