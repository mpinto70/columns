#pragma once

#include "gui/Color.h"
#include "gui/Font.h"
#include "gui/Point.h"
#include "gui/Rectangle.h"
#include "state/State.h"

#include <memory>
#include <string>

namespace graphics {

class Window {
public:
    Window(const std::string& name,
          size_t width,
          size_t height);
    virtual ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    const std::string& name() const { return name_; }
    size_t width() const { return width_; }
    size_t height() const { return height_; }

    virtual void clear() = 0;
    virtual void update() = 0;

    void draw(const state::State& state);

    void line(const gui::Point& begin,
          const gui::Point& end,
          gui::Color color);

    void rectangle(const gui::Rectangle& rectangle, gui::Color color);

    void rectangle(const gui::Point& top_left,
          const gui::Point& bottom_right,
          gui::Color color);

    void fill(const gui::Rectangle& rectangle, gui::Color color);

    void fill(const gui::Point& top_left,
          const gui::Point& bottom_right,
          gui::Color color);

    gui::Rectangle write(const std::string& text,
          const gui::Point& point,
          const gui::Font& font,
          gui::Color color);

private:
    std::string name_;
    size_t width_;
    size_t height_;

    virtual void line_(size_t x1,
          size_t y1,
          size_t x2,
          size_t y2,
          gui::Color color) = 0;

    virtual void rectangle_(size_t x1,
          size_t y1,
          size_t x2,
          size_t y2,
          gui::Color color) = 0;

    virtual void fill_(size_t x1,
          size_t y1,
          size_t x2,
          size_t y2,
          gui::Color color) = 0;

    virtual gui::Rectangle write_(const std::string& text,
          size_t x,
          size_t y,
          const gui::Font& font,
          gui::Color color) = 0;

    virtual void draw_(piece::SharedConstBoard board) = 0;
    virtual void draw_(const piece::Piece& piece, const piece::PiecePosition& piece_position) = 0;
    virtual void draw_next_(const piece::Piece& next_piece) = 0;
    virtual void draw_(const state::ScoreBoard& score_board) = 0;
    virtual void draw_(const piece::Board::EliminationList& elimination_list) = 0;
};

using WindowPtr = std::unique_ptr<Window>;
}
