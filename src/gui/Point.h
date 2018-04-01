#pragma once

#include <utility>

namespace gui {

/// Represents a 2D point
struct Point {
    /// Create a point at origin
    constexpr Point()
          : X(0),
            Y(0) {
    }
    constexpr Point(size_t x,
          size_t y)
          : X(x),
            Y(y) {
    }
    size_t X;
    size_t Y;
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
