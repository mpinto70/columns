#include "Window.h"

#include <stdexcept>

namespace grafico {
Window::Window(const std::string& name,
      const uint16_t width,
      const uint16_t height)
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
      const gui::Color& color) {
    line_(begin.X, begin.Y, end.X, end.Y, color);
}

void Window::rectangle(const gui::Rectangle& rectangle,
      const gui::Color& color) {
    rectangle_(rectangle.P1().X, rectangle.P1().Y, rectangle.P2().X, rectangle.P2().Y, color);
}

void Window::rectangle(const gui::Point& top_left,
      const gui::Point& bottom_right,
      const gui::Color& color) {
    rectangle_(top_left.X, top_left.Y, bottom_right.X, bottom_right.Y, color);
}

void Window::fill(const gui::Rectangle& rectangle,
      const gui::Color& color) {
    fill_(rectangle.P1().X, rectangle.P1().Y, rectangle.P2().X, rectangle.P2().Y, color);
}

void Window::fill(const gui::Point& top_left,
      const gui::Point& bottom_right,
      const gui::Color& color) {
    fill_(top_left.X, top_left.Y, bottom_right.X, bottom_right.Y, color);
}

gui::Rectangle Window::write(const std::string& text,
      const gui::Point& point,
      const gui::Font& font,
      const gui::Color& color) {
    return write_(text, point.X, point.Y, font, color);
}
}
