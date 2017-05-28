
#ifndef POSICAOPECA_H_mhpa
#define POSICAOPECA_H_mhpa

#include "peca/Tabuleiro.h"
#include <cstddef>
#include <cstdint>

namespace peca {

/** Respons�vel por marcar a posi��o da pe�a caindo no tabuleiro. */
class PosicaoPeca {
    public:
        /** Cria uma posi��o para um tabuleiro.
         * @param tab o tabuleiro
         * @param col a coluna
         * @param maxSubLinha o m�ximo de divis�o do passo
         */
        PosicaoPeca(const Tabuleiro & tab,
                    uint16_t col,
                    uint16_t maxSubLinha);
        /** Cria uma c�pia de \b rhs.
         * @param rhs a posi��o sendo copiada
         */
        PosicaoPeca(const PosicaoPeca & rhs);
        /** Copia o conte�do de \b rhs.
         * @param rhs a posi��o sendo copiada
         * @return refer�ncia ao objeto criado
         */
        PosicaoPeca & operator =(const PosicaoPeca & rhs);
        /** Anda um passo para baixo.
         * @throw std::logic_error � lan�ada caso n�o seja mais poss�vel dar um passo
         */
        void caiUmPasso();
        /** @return a coluna da posi��o. */
        uint16_t coluna() const { return coluna_; }
        /** @return a linha da posi��o. */
        uint16_t linha() const { return linha_; }
        /** @return a sub-linha da posi��o. */
        uint16_t subLinha() const { return subLinha_; }
        /** @return o valor limite do subLinha. */
        uint16_t maxSubLinha() const { return maxSubLinha_; }
        /** @return o limite para coluna_ (coluna_ < maxColuna_). */
        uint16_t maxColuna() const { return maxColuna_; }
        /** @return o limite para linha_ (linha_ <= maxLinha_ - TAMANHO_PECA). */
        uint16_t maxLinha() const { return maxLinha_; }
        /** Move para esquerda.
         * @throws std::logic_error � lan�ada caso n�o seja poss�vel mover para esquerda.
         */
        void moveEsquerda();
        /** Move para direita.
         * @throws std::logic_error � lan�ada caso n�o seja poss�vel mover para direita.
         */
        void moveDireita();
        /** @return se a pe�a chegou ao fundo do tabuleiro. */
        bool chegouAoFundo() const { return linha_ + TAMANHO_PECA == maxLinha_; }
    private:
        uint16_t coluna_;       ///< a coluna em que est� a pe�a
        uint16_t linha_;        ///< a linha em que est� a pe�a
        uint16_t subLinha_;     ///< a sub-linha em que est� a pe�a [0 <--> maxSubLinha_ - 1]
        uint16_t maxSubLinha_;  ///< o n�mero de subdivis�es internas de posi��o
        uint16_t maxColuna_;    ///< restri��o: coluna_ < maxColuna_
        uint16_t maxLinha_;     ///< maior linha do tabuleiro
};

/** @return se duas posi��es s�o iguais.
 * @param lhs a pe�a do lado esquerdo da igualdade
 * @param rhs a pe�a do lado direito da igualdade
 */
bool operator == (const PosicaoPeca & lhs, const PosicaoPeca & rhs);

}

#endif
