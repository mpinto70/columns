#include "Window.h"

#include <stdexcept>

namespace graphics {
Window::Window(const std::string& name,
      const size_t width,
      const size_t height)
      : name_(name),
        width_(width),
        height_(height) {
    if (name == "") {
        throw std::invalid_argument("Window - empty name");
    }
    if (width_ == 0) {
        throw std::invalid_argument("Window - zero width");
    }
    if (height_ == 0) {
        throw std::invalid_argument("Window - zero height");
    }
}

Window::~Window() = default;

void Window::line(const gui::Point& begin,
      const gui::Point& end,
      gui::Color color) {
    line_(begin.X, begin.Y, end.X, end.Y, color);
}

void Window::rectangle(const gui::Rectangle& rectangle, gui::Color color) {
    rectangle_(rectangle.P1().X, rectangle.P1().Y, rectangle.P2().X, rectangle.P2().Y, color);
}

void Window::rectangle(const gui::Point& top_left,
      const gui::Point& bottom_right,
      gui::Color color) {
    rectangle_(top_left.X, top_left.Y, bottom_right.X, bottom_right.Y, color);
}

void Window::fill(const gui::Rectangle& rectangle, gui::Color color) {
    fill_(rectangle.P1().X, rectangle.P1().Y, rectangle.P2().X, rectangle.P2().Y, color);
}

void Window::fill(const gui::Point& top_left,
      const gui::Point& bottom_right,
      gui::Color color) {
    fill_(top_left.X, top_left.Y, bottom_right.X, bottom_right.Y, color);
}

gui::Rectangle Window::write(const std::string& text,
      const gui::Point& point,
      const gui::Font& font,
      gui::Color color) {
    return write_(text, point.X, point.Y, font, color);
}

void Window::draw(const state::State& state) {
    clear();
    draw_(state.board());
    draw_(state.score_board());
    if (state.has_piece_falling()) {
        draw_(state.piece(), state.piece_position());
    }
    if (state.has_elimination_list()) {
        draw_(state.elimination_list());
    }
    if (state.has_next()) {
        draw_next_(state.next());
    }
}
}
