
#ifndef PLACAR_H_mhpa
#define PLACAR_H_mhpa

#include "pontuacao/Pontuacao.h"

namespace pontuacao {
/** Responsável armazenar e processar um placar (recorde/pontos). */
class Placar {
    public:
        /** Cria o objeto.
         * @param recorde   o recorde
         * @param pontos    a pontuação inicial
         */
        Placar(const Pontuacao & recorde = Pontuacao(0),
               const Pontuacao & pontos = Pontuacao(0));
        /** @return o recorde atual. */
        const Pontuacao & recorde() const { return recorde_; }
        /** @return a pontuação atual. */
        const Pontuacao & pontuacao() const { return pontuacao_; }
        /** Acrescenta pontos ao total da pontuação corrente.
         * @param n a quantidade de peças que foram unidas e sumiram
         */
        void acrescenta(size_t n);
        /** Zera a pontuação. */
        void zera();
    private:
        Pontuacao recorde_;     ///< o recorde
        Pontuacao pontuacao_;   ///< a pontuação
};

/** @return se os dois placares são iguais.
 * @param lhs o objeto à esquerda da igualdade
 * @param rhs o objeto à direita da igualdade
 */
bool operator == (const Placar & lhs, const Placar & rhs);
}
#endif
