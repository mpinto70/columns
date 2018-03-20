#pragma once

#include "gui/Color.h"
#include "gui/Font.h"
#include "gui/Point.h"
#include "gui/Rectangle.h"

#include <cstdint>
#include <memory>
#include <string>

namespace grafico {

class Window {
public:
    Window(const std::string& name,
          uint16_t width,
          uint16_t height);
    virtual ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    const std::string& name() const { return name_; }
    uint16_t width() const { return width_; }
    uint16_t height() const { return height_; }

    virtual void clear() = 0;
    virtual void update() = 0;

    void line(const gui::Point& begin,
          const gui::Point& end,
          const gui::Color& color);

    void rectangle(const gui::Rectangle& rectangle,
          const gui::Color& color);

    void rectangle(const gui::Point& top_left,
          const gui::Point& bottom_right,
          const gui::Color& color);

    void fill(const gui::Rectangle& rectangle,
          const gui::Color& color);

    void fill(const gui::Point& top_left,
          const gui::Point& bottom_right,
          const gui::Color& color);

    gui::Rectangle write(const std::string& text,
          const gui::Point& point,
          const gui::Font& font,
          const gui::Color& color);

private:
    std::string name_;
    uint16_t width_;
    uint16_t height_;

    virtual void line_(uint16_t x1,
          uint16_t y1,
          uint16_t x2,
          uint16_t y2,
          const gui::Color& color) = 0;

    virtual void rectangle_(uint16_t x1,
          uint16_t y1,
          uint16_t x2,
          uint16_t y2,
          const gui::Color& color) = 0;

    virtual void fill_(uint16_t x1,
          uint16_t y1,
          uint16_t x2,
          uint16_t y2,
          const gui::Color& color) = 0;

    virtual gui::Rectangle write_(const std::string& text,
          uint16_t x,
          uint16_t y,
          const gui::Font& font,
          const gui::Color& color) = 0;
};

using SharedJanela = std::shared_ptr<Window>;
}
