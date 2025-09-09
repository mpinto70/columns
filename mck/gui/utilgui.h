#pragma once

#include "gui/Color.h"
#include "gui/Font.h"

namespace gui {
bool operator==(const Font& lhs, const Font& rhs);
bool operator!=(const Font& lhs, const Font& rhs);

namespace mck {

std::string to_string(gui::Color color);
Color to_color(size_t value);
size_t from_color(Color color);
Color to_normalized_color(size_t value);

constexpr size_t end_color() {
    return static_cast<size_t>(Color::NONE);
}

void print(Color color);
void print(const std::string& file, int line, Color color);
} // namespace mck
} // namespace gui
