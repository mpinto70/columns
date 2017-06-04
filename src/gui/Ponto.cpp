
#include "Ponto.h"
#include <algorithm>

namespace gui {

void Ponto::swap(Ponto& rhs) {
    std::swap(X, rhs.X);
    std::swap(Y, rhs.Y);
}

bool operator == (const Ponto& lhs, const Ponto& rhs) {
    return lhs.X == rhs.X
           && lhs.Y == rhs.Y;
}

bool operator != (const Ponto& lhs, const Ponto& rhs) {
    return not(lhs == rhs);
}

}
