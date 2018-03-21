#pragma once

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
Color darken(Color color, unsigned char percent);

constexpr Color RED{ 255, 0, 0 };
constexpr Color GREEN{ 0, 255, 0 };
constexpr Color BLUE{ 0, 0, 255 };
constexpr Color WHITE{ 255, 255, 255 };
constexpr Color BLACK{ 0, 0, 0 };
constexpr Color GRAY{ 127, 127, 127 };
constexpr Color YELLOW{ 255, 255, 0 };
constexpr Color LAVENDER{ 153, 102, 255 };
}
