#include "Score.h"

#include "piece/Piece.h"

#include <stdexcept>

namespace state {

void Score::add(size_t n) {
    if (n < 3) {
        return;
    }
    n -= 3 - 1;
    n *= n;
    const size_t res = total_ + n;
    if (res < total_) { // overflow
        return;
    }
    total_ = res;
}
}
