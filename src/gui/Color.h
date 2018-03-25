#pragma once

#include <stdexcept>

namespace gui {

/// Represents an RGB color
struct Color {
    /// Creates a black color.
    constexpr Color()
          : R(0),
            G(0),
            B(0) {
    }
    /**
     * @param r red intensity [0 - 255]
     * @param g green intensity [0 - 255]
     * @param b blue intensity [0 - 255]
     */
    constexpr Color(unsigned char r,
          unsigned char g,
          unsigned char b)
          : R(r),
            G(g),
            B(b) {
    }
    unsigned char R; ///< red intensity [0 - 255]
    unsigned char G; ///< green intensity [0 - 255]
    unsigned char B; ///< blue intensity [0 - 255]
};

constexpr bool operator==(const Color& lhs, const Color& rhs) {
    return lhs.R == rhs.R
           && lhs.G == rhs.G
           && lhs.B == rhs.B;
}

constexpr bool operator!=(const Color& lhs, const Color& rhs) {
    return not(lhs == rhs);
}

/** @return darken the color by \p percent %.
 * @param color base color
 * @param percent darkening percentage
 */
constexpr Color darken(Color color, unsigned char percent) {
    const double factor = (100 - percent) / 100.0;
    return Color(factor * color.R, factor * color.G, factor * color.B);
}

constexpr Color RED{ 0x98, 0x1b, 0x1e };
constexpr Color GREEN{ 0x2e, 0x85, 0x40 };
constexpr Color BLUE{ 0x02, 0xbf, 0xe7 };
constexpr Color WHITE{ 0xf1, 0xf1, 0xf1 };
constexpr Color BLACK{ 0, 0, 0 };
constexpr Color GRAY{ 127, 127, 127 };
constexpr Color YELLOW{ 0xfd, 0xb8, 0x1e };
constexpr Color LAVENDER{ 0x4c, 0x2c, 0x92 };
}
