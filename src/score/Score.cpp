#include "Score.h"

#include "piece/Piece.h"

#include <stdexcept>

namespace score {

void Score::add(size_t n) {
    if (n < 3) {
        throw std::invalid_argument("Score::add - invalid number of tiles");
    }
    n -= 3 - 1;
    n *= n;
    const size_t res = total_ + n;
    if (res < total_) { // overflow
        throw std::invalid_argument("Score::add - score overflow. Congrats!!!");
    }
    total_ = res;
}
}
