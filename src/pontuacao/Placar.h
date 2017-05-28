
#ifndef PLACAR_H_mhpa
#define PLACAR_H_mhpa

#include "pontuacao/Pontuacao.h"

namespace pontuacao {
/** Respons�vel armazenar e processar um placar (recorde/pontos). */
class Placar {
    public:
        /** Cria o objeto.
         * @param recorde   o recorde
         * @param pontos    a pontua��o inicial
         */
        Placar(const Pontuacao & recorde = Pontuacao(0),
               const Pontuacao & pontos = Pontuacao(0));
        /** @return o recorde atual. */
        const Pontuacao & recorde() const { return recorde_; }
        /** @return a pontua��o atual. */
        const Pontuacao & pontuacao() const { return pontuacao_; }
        /** Acrescenta pontos ao total da pontua��o corrente.
         * @param n a quantidade de pe�as que foram unidas e sumiram
         */
        void acrescenta(size_t n);
        /** Zera a pontua��o. */
        void zera();
    private:
        Pontuacao recorde_;     ///< o recorde
        Pontuacao pontuacao_;   ///< a pontua��o
};

/** @return se os dois placares s�o iguais.
 * @param lhs o objeto � esquerda da igualdade
 * @param rhs o objeto � direita da igualdade
 */
bool operator == (const Placar & lhs, const Placar & rhs);
}
#endif
