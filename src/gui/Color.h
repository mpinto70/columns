#pragma once

#include <cstddef>

namespace gui {

enum class Color {
    RED,
    GREEN,
    BLUE,
    GRAY,
    YELLOW,
    LAVENDER,
    BLACK,
    NONE,
};

constexpr Color darken(Color color, unsigned char percent) {
    return color;
}
}
