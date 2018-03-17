#include "Peca.h"

#include "util/Random.h"

#include <stdexcept>
#include <utility>

namespace peca {

Peca::Peca(const gui::Color (&cores)[TAMANHO_PECA])
      : cores_(cores) {
}

Peca::Peca(const std::vector<gui::Color>& cores) {
    if (cores.size() != TAMANHO_PECA) {
        throw std::invalid_argument("Peca - tamanho do vetor invalido");
    }

    for (unsigned char i = 0; i < TAMANHO_PECA; ++i) {
        cores_[i] = cores[i];
    }
}

const gui::Color& Peca::operator[](unsigned char i) const {
    if (i >= TAMANHO_PECA) {
        throw std::invalid_argument("Peca[" + std::to_string(i) + "] - índice fora dos limites");
    }
    return cores_[i];
}

void Peca::rolaParaCima() {
    const gui::Color tmp = cores_[0];
    for (unsigned char i = 1; i < TAMANHO_PECA; ++i) {
        cores_[i - 1] = cores_[i];
    }
    cores_[TAMANHO_PECA - 1] = tmp;
}

void Peca::rolaParaBaixo() {
    const gui::Color tmp = cores_[TAMANHO_PECA - 1];
    for (unsigned char i = TAMANHO_PECA - 1; i > 0; --i) {
        cores_[i] = cores_[i - 1];
    }
    cores_[0] = tmp;
}

Peca Peca::cria(const std::vector<gui::Color>& coresPossiveis) {
    if (coresPossiveis.empty()) {
        throw std::invalid_argument("Peca::cria - sem cores a sortear");
    }
    gui::Color cores[TAMANHO_PECA];
    for (unsigned char i = 0; i < peca::TAMANHO_PECA; ++i) {
        const gui::Color& rgb(coresPossiveis.at(util::Random::get(coresPossiveis.size() - 1)));
        cores[i] = rgb;
    }
    return peca::Peca(cores);
}

bool operator==(const Peca& lhs, const Peca& rhs) {
    using namespace std::rel_ops;
    for (unsigned char i = 0; i < TAMANHO_PECA; ++i)
        if (lhs[i] != rhs[i]) {
            return false;
        }
    return true;
}

bool operator!=(const Peca& lhs, const Peca& rhs) {
    return not(lhs == rhs);
}
}
