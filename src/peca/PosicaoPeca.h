
#ifndef POSICAOPECA_H_mhpa
#define POSICAOPECA_H_mhpa

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
        PosicaoPeca(const Tabuleiro & tab,
                    uint16_t col,
                    uint16_t maxSubLinha);
        /** Cria uma cópia de \b rhs.
         * @param rhs a posição sendo copiada
         */
        PosicaoPeca(const PosicaoPeca & rhs);
        /** Copia o conteúdo de \b rhs.
         * @param rhs a posição sendo copiada
         * @return referência ao objeto criado
         */
        PosicaoPeca & operator =(const PosicaoPeca & rhs);
        /** Anda um passo para baixo.
         * @throw std::logic_error é lançada caso não seja mais possível dar um passo
         */
        void caiUmPasso();
        /** @return a coluna da posição. */
        uint16_t coluna() const { return coluna_; }
        /** @return a linha da posição. */
        uint16_t linha() const { return linha_; }
        /** @return a sub-linha da posição. */
        uint16_t subLinha() const { return subLinha_; }
        /** @return o valor limite do subLinha. */
        uint16_t maxSubLinha() const { return maxSubLinha_; }
        /** @return o limite para coluna_ (coluna_ < maxColuna_). */
        uint16_t maxColuna() const { return maxColuna_; }
        /** @return o limite para linha_ (linha_ <= maxLinha_ - TAMANHO_PECA). */
        uint16_t maxLinha() const { return maxLinha_; }
        /** Move para esquerda.
         * @throws std::logic_error é lançada caso não seja possível mover para esquerda.
         */
        void moveEsquerda();
        /** Move para direita.
         * @throws std::logic_error é lançada caso não seja possível mover para direita.
         */
        void moveDireita();
        /** @return se a peça chegou ao fundo do tabuleiro. */
        bool chegouAoFundo() const { return linha_ + TAMANHO_PECA == maxLinha_; }
    private:
        uint16_t coluna_;       ///< a coluna em que está a peça
        uint16_t linha_;        ///< a linha em que está a peça
        uint16_t subLinha_;     ///< a sub-linha em que está a peça [0 <--> maxSubLinha_ - 1]
        uint16_t maxSubLinha_;  ///< o número de subdivisões internas de posição
        uint16_t maxColuna_;    ///< restrição: coluna_ < maxColuna_
        uint16_t maxLinha_;     ///< maior linha do tabuleiro
};

/** @return se duas posições são iguais.
 * @param lhs a peça do lado esquerdo da igualdade
 * @param rhs a peça do lado direito da igualdade
 */
bool operator == (const PosicaoPeca & lhs, const PosicaoPeca & rhs);

}

#endif
