#pragma once

#include <cstdint>
#include <utility>

namespace gui {

/// Represents a 2D point
struct Point {
    /// Create a point at origin
    constexpr Point()
          : X(0),
            Y(0) {
    }
    constexpr Point(uint16_t x,
          uint16_t y)
          : X(x),
            Y(y) {
    }
    uint16_t X;
    uint16_t Y;
};

constexpr Point operator+(const Point& lhs, const Point& rhs) {
    return Point(lhs.X + rhs.X, lhs.Y + rhs.Y);
}

constexpr Point operator-(const Point& lhs, const Point& rhs) {
    return Point(lhs.X - rhs.X, lhs.Y - rhs.Y);
}

constexpr bool operator==(const Point& lhs, const Point& rhs) {
    return lhs.X == rhs.X
           && lhs.Y == rhs.Y;
}

constexpr bool operator!=(const Point& lhs, const Point& rhs) {
    return not(lhs == rhs);
}
}
