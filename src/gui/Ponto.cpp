
#include "Ponto.h"
#include <algorithm>

namespace gui {

bool operator==(const Ponto& lhs, const Ponto& rhs) {
    return lhs.X == rhs.X
           && lhs.Y == rhs.Y;
}

bool operator!=(const Ponto& lhs, const Ponto& rhs) {
    return not(lhs == rhs);
}
}
