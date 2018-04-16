#include "utilgui.h"

#include <cstdio>
#include <stdexcept>
#include <string>

namespace gui {
bool operator==(const Font& lhs, const Font& rhs) {
    return lhs.name() == rhs.name()
           && lhs.size() == rhs.size();
}

bool operator!=(const Font& lhs, const Font& rhs) {
    return not(lhs == rhs);
}

namespace mck {

std::string to_string(gui::Color color) {
    switch (color) {
        case Color::NONE: return "none";
        case Color::RED: return "RED";
        case Color::GREEN: return "GREEN";
        case Color::BLUE: return "BLUE";
        case Color::BLACK: return "BLACK";
        case Color::GRAY: return "GRAY";
        case Color::YELLOW: return "YELLOW";
        case Color::LAVENDER: return "LAVENDER";
    }
    throw std::invalid_argument("invalid color " + std::to_string(static_cast<size_t>(color)));
}

Color to_color(size_t value) {
    return static_cast<Color>(value);
}

Color to_normalized_color(size_t value) {
    return to_color(value % end_color());
}

void print(gui::Color color) {
    printf("%s |", to_string(color).c_str());
}

void print(const std::string& file,
      int line,
      Color color) {
    printf("Printing color from %s(%d)\n", file.c_str(), line);
    const std::string separator(11, '-');
    printf("%s\n", separator.c_str());
    print(color);
    printf("\n");
    printf("%s\n\n", separator.c_str());
}
}
}
