#pragma once

#include "peca/Tabuleiro.h"
#include <cstddef>
#include <cstdint>

namespace peca {

/** Responsável por marcar a posição da peça caindo no tabuleiro. */
class PosicaoPeca {
public:
    /** Cria uma posição para um tabuleiro.
     * @param tab o tabuleiro
     * @param col a coluna
     * @param maxSubLinha o máximo de divisão do passo
     */
    PosicaoPeca(const Tabuleiro& tab,
          uint16_t col,
          uint16_t maxSubLinha);
    /** Anda um passo para baixo.
     * @throw std::logic_error é lançada caso não seja mais possível dar um passo
     */
    void caiUmPasso();
    uint16_t coluna() const { return coluna_; }
    uint16_t linha() const { return linha_; }
    uint16_t subLinha() const { return subLinha_; }
    uint16_t maxSubLinha() const { return maxSubLinha_; }
    uint16_t maxColuna() const { return maxColuna_; }
    uint16_t maxLinha() const { return maxLinha_; }
    void moveEsquerda();
    void moveDireita();
    bool chegouAoFundo() const { return linha_ + TAMANHO_PECA == maxLinha_; }

private:
    uint16_t coluna_;      ///< a coluna em que está a peça
    uint16_t linha_;       ///< a linha em que está a peça
    uint16_t subLinha_;    ///< a sub-linha em que está a peça [0 <--> maxSubLinha_ - 1]
    uint16_t maxSubLinha_; ///< o número de subdivisões internas de posição
    uint16_t maxColuna_;   ///< restrição: coluna_ < maxColuna_
    uint16_t maxLinha_;    ///< maior linha do tabuleiro
};

bool operator==(const PosicaoPeca& lhs, const PosicaoPeca& rhs);
bool operator!=(const PosicaoPeca& lhs, const PosicaoPeca& rhs);
}
