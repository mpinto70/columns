#include "ScoreBoardDrawer.h"

namespace graphics {
ScoreBoardDrawer::ScoreBoardDrawer(const gui::Rectangle& box,
      const gui::Font& title_font,
      const gui::Font& score_font,
      gui::Color title_color,
      gui::Color score_color)
      : box_(box),
        title_font_(title_font),
        score_font_(score_font),
        border_color_(gui::Color::GRAY),
        title_color_(title_color),
        score_color_(score_color),
        record_color_(gui::darken(score_color, 20)) {
}

void ScoreBoardDrawer::draw(Window& window, const state::State& state) const {
    const auto& score_board = state.score_board();
    window.fill(box_, gui::Color::NONE);
    window.rectangle(box_, border_color_);
    window.write("Score", box_.P1() + gui::Point{ 3, 3 }, title_font_, title_color_);
    window.write("you", box_.P1() + gui::Point{ 3, 18 }, score_font_, score_color_);
    window.write("record", box_.P1() + gui::Point{ 3, 33 }, score_font_, record_color_);
    window.write(std::to_string(score_board.score().total()), box_.P1() + gui::Point{ 25, 18 }, score_font_, score_color_);
    window.write(std::to_string(score_board.record().total()), box_.P1() + gui::Point{ 25, 33 }, score_font_, record_color_);
}
}
