
#include "Tabuleiro.h"
#include <stdexcept>
#include <utility>

namespace peca {

Tabuleiro::Tabuleiro(const uint16_t l,
                     const uint16_t h,
                     const gui::Cor & cor)
    : casas_(l * h, cor),
      cor_(cor),
      largura_(l),
      altura_(h) {
    if (l < TAMANHO_PECA)
        throw std::invalid_argument("Tabuleiro - largura insuficiente");
    if (h < 2 * TAMANHO_PECA)
        throw std::invalid_argument("Tabuleiro - altura insuficiente");
}

Tabuleiro::Tabuleiro(const Tabuleiro & rhs)
    : casas_(rhs.casas_),
      cor_(rhs.cor_),
      largura_(rhs.largura_),
      altura_(rhs.altura_) {
}

Tabuleiro & Tabuleiro::operator = (const Tabuleiro & rhs) {
    auto tmp = rhs.casas_;
    casas_.swap(tmp);
    cor_ = rhs.cor_;
    largura_ = rhs.largura_;
    altura_ = rhs.altura_;
    return *this;
}

const gui::Cor & Tabuleiro::at(const uint16_t c, const uint16_t l) const {
    if (c >= largura_)
        throw std::invalid_argument("Tabuleiro::at const - overflow de coluna " + std::to_string(c));
    if (l >= altura_)
        throw std::invalid_argument("Tabuleiro::at const - overflow de linha " + std::to_string(l));
    return casas_.at(l * largura_ + c);
}

gui::Cor & Tabuleiro::at(const uint16_t c, const uint16_t l) {
    if (c >= largura_)
        throw std::invalid_argument("Tabuleiro::at - overflow de coluna " + std::to_string(c));
    if (l >= altura_)
        throw std::invalid_argument("Tabuleiro::at - overflow de linha " + std::to_string(l));
    return casas_.at(l * largura_ + c);
}

void Tabuleiro::elimina(const uint16_t c, const uint16_t l) {
    for (uint16_t j = l; j > 0; --j) {
        at(c, j) = at(c, j - 1);
    }
    at(c, 0) = cor_;
}

bool operator == (const Tabuleiro & lhs, const Tabuleiro & rhs) {
    if (lhs.altura() != rhs.altura()) return false;
    if (lhs.largura() != rhs.largura()) return false;
    if (lhs.casas() != rhs.casas()) return false;
    return true;
}
}
