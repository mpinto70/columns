
#ifndef PONTUACAO_H_mhpa
#define PONTUACAO_H_mhpa

#include <cstdio>

/** namespace das entidades relacionadas à pontuação. */
namespace pontuacao {
/** Responsável armazenar e processar a pontuação. */
class Pontuacao {
    public:
        /** Cria o objeto.
         * @param total a pontuação inicial
         */
        Pontuacao(size_t total = 0);
        /** @return o total de pontos. */
        size_t total() const { return total_; }
        /** Acrescenta pontos ao total devido à junção de \b n peças.
         * @param n a quantidade de peças que foram unidas e sumiram
         */
        void acrescenta(size_t n);
        /** Zera a pontuação. */
        void zera() { total_ = 0; }
    private:
        size_t total_;      ///< a pontuação
};

/** @return se as duas pontuações são iguais.
 * @param lhs o objeto à esquerda da igualdade
 * @param rhs o objeto à direita da igualdade
 */
bool operator == (const Pontuacao & lhs, const Pontuacao & rhs);
/** @return se a primeira pontuação é menor que a segunda.
 * @param lhs o objeto à esquerda da comparação
 * @param rhs o objeto à direita da comparação
 */
bool operator < (const Pontuacao & lhs, const Pontuacao & rhs);
}
#endif
