#include "Pontuacao.h"

#include "piece/Piece.h"

#include <stdexcept>

namespace pontuacao {

Pontuacao::Pontuacao(const size_t total)
      : total_(total) {
}

void Pontuacao::acrescenta(size_t n) {
    if (n < piece::PIECE_SIZE) {
        throw std::invalid_argument("Pontuacao::acrescenta - quantidade inválida de peças unidas");
    }
    n -= piece::PIECE_SIZE - 1;
    n *= n;
    const size_t res = total_ + n;
    if (res < total_) { // overflow
        throw std::invalid_argument("Pontuacao::acrescenta - pontuação ultrapassou o limite");
    }
    total_ = res;
}

bool operator==(const Pontuacao& lhs, const Pontuacao& rhs) {
    return lhs.total() == rhs.total();
}

bool operator!=(const Pontuacao& lhs, const Pontuacao& rhs) {
    return not(lhs == rhs);
}

bool operator<(const Pontuacao& lhs, const Pontuacao& rhs) {
    return lhs.total() < rhs.total();
}
}
