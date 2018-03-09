
#include "Placar.h"
#include <stdexcept>
#include <string>

namespace pontuacao {

Placar::Placar(const Pontuacao& recorde,
      const Pontuacao& pontos)
      : recorde_(recorde),
        pontuacao_(pontos) {
    if (recorde_ < pontuacao_)
        throw std::invalid_argument("Placar - recorde ("
                                    + std::to_string(recorde.total())
                                    + ") é inferior à pontuação ("
                                    + std::to_string(pontos.total())
                                    + ")");
}

void Placar::acrescenta(const size_t n) {
    pontuacao_.acrescenta(n);
    if (recorde_ < pontuacao_) {
        recorde_ = pontuacao_;
    }
}

void Placar::zera() {
    pontuacao_.zera();
}

bool operator==(const Placar& lhs, const Placar& rhs) {
    return lhs.recorde() == rhs.recorde()
           && lhs.pontuacao() == rhs.pontuacao();
}

bool operator!=(const Placar& lhs, const Placar& rhs) {
    return not(lhs == rhs);
}
}
