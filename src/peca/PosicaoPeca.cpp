
#include "PosicaoPeca.h"
#include "peca/Tabuleiro.h"
#include <stdexcept>

namespace peca {

PosicaoPeca::PosicaoPeca(const Tabuleiro& tab,
      const uint16_t col,
      const uint16_t maxSubLinha)
      : coluna_(col),
        linha_(0),
        subLinha_(0),
        maxSubLinha_(maxSubLinha),
        maxColuna_(tab.largura()),
        maxLinha_(tab.altura()) {
    if (maxSubLinha_ == 0) {
        throw std::invalid_argument("PosicaoPeca - máxima subdivisão da posição nula");
    }
    if (col >= tab.largura()) {
        throw std::invalid_argument("PosicaoPeca - coluna ultrapassa o largura do tabuleiro");
    }
}

void PosicaoPeca::caiUmPasso() {
    if (linha_ + TAMANHO_PECA == maxLinha_) {
        throw std::logic_error("PosicaoPeca::caiUmPasso - já está na posição inferior");
    }
    if (subLinha_ == maxSubLinha_ - 1) {
        subLinha_ = 0;
        ++linha_;
    } else {
        ++subLinha_;
    }
}

void PosicaoPeca::moveEsquerda() {
    if (coluna_ == 0) {
        throw std::logic_error("PosicaoPeca::moveEsquerda - não é possível mover para esquerda");
    }
    --coluna_;
}

void PosicaoPeca::moveDireita() {
    if (coluna_ + 1 == maxColuna_) {
        throw std::logic_error("PosicaoPeca::moveEsquerda - não é possível mover para direita");
    }
    ++coluna_;
}

bool operator==(const PosicaoPeca& lhs,
      const PosicaoPeca& rhs) {
    if (lhs.coluna() != rhs.coluna()) {
        return false;
    }
    if (lhs.linha() != rhs.linha()) {
        return false;
    }
    if (lhs.subLinha() != rhs.subLinha()) {
        return false;
    }
    if (lhs.maxSubLinha() != rhs.maxSubLinha()) {
        return false;
    }
    return true;
}

bool operator!=(const PosicaoPeca& lhs,
      const PosicaoPeca& rhs) {
    return not(lhs == rhs);
}
}
