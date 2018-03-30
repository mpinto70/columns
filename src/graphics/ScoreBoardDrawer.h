#pragma once

#include "graphics/Drawer.h"

namespace graphics {
class ScoreBoardDrawer : public Drawer {
public:
    ScoreBoardDrawer(const gui::Rectangle& box,
          const gui::Font& title_font,
          const gui::Font& score_font,
          const gui::Color& background,
          const gui::Color& title_color,
          const gui::Color& score_color);

    ~ScoreBoardDrawer() override = default;

    void draw(Window& window, const state::State& state) const override;

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
