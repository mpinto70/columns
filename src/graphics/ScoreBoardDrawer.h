#pragma once

#include "graphics/Window.h"
#include "state/ScoreBoard.h"

namespace graphics {
class ScoreBoardDrawer {
public:
    ScoreBoardDrawer(const gui::Rectangle& box,
          const gui::Font& title_font,
          const gui::Font& score_font,
          const gui::Color& background,
          const gui::Color& title_color,
          const gui::Color& score_color);

    void draw(SharedWindow window, const state::ScoreBoard& score_board) const;

    const gui::Rectangle& box() const { return box_; }
    const gui::Font& title_font() const { return title_font_; }
    const gui::Font& score_font() const { return score_font_; }
    const gui::Color& background() const { return background_; }
    const gui::Color& border_color() const { return border_color_; }
    const gui::Color& title_color() const { return title_color_; }
    const gui::Color& score_color() const { return score_color_; }
    const gui::Color& record_color() const { return record_color_; }

private:
    gui::Rectangle box_;
    gui::Font title_font_;
    gui::Font score_font_;
    gui::Color background_;
    gui::Color border_color_;
    gui::Color title_color_;
    gui::Color score_color_;
    gui::Color record_color_;
};
}
