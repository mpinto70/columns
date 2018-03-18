#pragma once

#include "gui/Point.h"

#include <algorithm>
#include <cstdint>

namespace gui {

/// Represents a rectangle
struct Rectangle {
public:
    /**
     * @param x1 x coordinate of corner 1
     * @param y1 y coordinate of corner 1
     * @param x2 x coordinate of corner 2
     * @param y2 y coordinate of corner 2
     */
    constexpr Rectangle(uint16_t x1,
          uint16_t y1,
          uint16_t x2,
          uint16_t y2)
          : P1_(std::min(x1, x2), std::min(y1, y2)),
            P2_(std::max(x1, x2), std::max(y1, y2)) {
    }

    /**
     * @param p1 one corner
     * @param p2 other corner
     */
    constexpr Rectangle(const Point& p1,
          const Point& p2)
          : Rectangle(p1.X, p1.Y, p2.X, p2.Y) {
    }

    constexpr const Point& P1() const { return P1_; }
    constexpr const Point& P2() const { return P2_; }

private:
    Point P1_; ///< top left corner
    Point P2_; ///< bottom right corner
};

constexpr bool operator==(const Rectangle& lhs, const Rectangle& rhs) {
    return lhs.P1() == rhs.P1()
           && lhs.P2() == rhs.P2();
}

constexpr bool operator!=(const Rectangle& lhs, const Rectangle& rhs) {
    return not(lhs == rhs);
}
}
