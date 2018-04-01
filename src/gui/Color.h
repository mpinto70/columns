#pragma once

#include <cstddef>

namespace gui {

enum class Color : size_t {
    RED,
    GREEN,
    BLUE,
    WHITE,
    BLACK,
    GRAY,
    YELLOW,
    LAVENDER,
};

constexpr Color darken(Color color, unsigned char percent) {
    return color;
}
}
