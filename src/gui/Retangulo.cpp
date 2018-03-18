#include "Retangulo.h"

#include <algorithm>

namespace gui {

Retangulo::Retangulo(const uint16_t x1,
      const uint16_t y1,
      const uint16_t x2,
      const uint16_t y2)
      : X1_(x1),
        Y1_(y1),
        X2_(x2),
        Y2_(y2) {
    if (X1_ > X2_) {
        std::swap(X1_, X2_);
    }
    if (Y1_ > Y2_) {
        std::swap(Y1_, Y2_);
    }
}

Retangulo::Retangulo(const Point& p1,
      const Point& p2)
      : Retangulo(p1.X, p1.Y, p2.X, p2.Y) {
}

bool operator==(const Retangulo& lhs, const Retangulo& rhs) {
    return lhs.X1() == rhs.X1()
           && lhs.Y1() == rhs.Y1()
           && lhs.X2() == rhs.X2()
           && lhs.Y2() == rhs.Y2();
}
}
