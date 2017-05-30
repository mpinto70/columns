
#include "Pontuacao.h"
#include "peca/Peca.h"
#include <stdexcept>

namespace pontuacao {

Pontuacao::Pontuacao(const size_t total)
    : total_(total) {
}

void Pontuacao::acrescenta(size_t n) {
    if (n < peca::TAMANHO_PECA)
        throw std::invalid_argument("Pontuacao::acrescenta - quantidade inválida de peças unidas");
    n -= peca::TAMANHO_PECA - 1;
    n *= n;
    const size_t res = total_ + n;
    if (res < total_) // overflow
        throw std::invalid_argument("Pontuacao::acrescenta - pontuação ultrapassou o limite");
    total_ = res;
}

bool operator == (const Pontuacao & lhs, const Pontuacao & rhs) {
    return lhs.total() == rhs.total();
}

bool operator != (const Pontuacao & lhs, const Pontuacao & rhs) {
    return not (lhs == rhs);
}

bool operator < (const Pontuacao & lhs, const Pontuacao & rhs) {
    return lhs.total() < rhs.total();
}

}
