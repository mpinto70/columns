#include "Score.h"

#include "piece/Piece.h"

#include <stdexcept>

namespace pontuacao {

void Score::add(size_t n) {
    if (n < piece::PIECE_SIZE) {
        throw std::invalid_argument("Score::add - invalid number of tiles");
    }
    n -= piece::PIECE_SIZE - 1;
    n *= n;
    const size_t res = total_ + n;
    if (res < total_) { // overflow
        throw std::invalid_argument("Score::add - score overflow. Congrats!!!");
    }
    total_ = res;
}
}
