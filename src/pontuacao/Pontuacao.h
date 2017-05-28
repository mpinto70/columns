
#ifndef PONTUACAO_H_mhpa
#define PONTUACAO_H_mhpa

#include <cstdio>

/** namespace das entidades relacionadas � pontua��o. */
namespace pontuacao {
/** Respons�vel armazenar e processar a pontua��o. */
class Pontuacao {
    public:
        /** Cria o objeto.
         * @param total a pontua��o inicial
         */
        Pontuacao(size_t total = 0);
        /** @return o total de pontos. */
        size_t total() const { return total_; }
        /** Acrescenta pontos ao total devido � jun��o de \b n pe�as.
         * @param n a quantidade de pe�as que foram unidas e sumiram
         */
        void acrescenta(size_t n);
        /** Zera a pontua��o. */
        void zera() { total_ = 0; }
    private:
        size_t total_;      ///< a pontua��o
};

/** @return se as duas pontua��es s�o iguais.
 * @param lhs o objeto � esquerda da igualdade
 * @param rhs o objeto � direita da igualdade
 */
bool operator == (const Pontuacao & lhs, const Pontuacao & rhs);
/** @return se a primeira pontua��o � menor que a segunda.
 * @param lhs o objeto � esquerda da compara��o
 * @param rhs o objeto � direita da compara��o
 */
bool operator < (const Pontuacao & lhs, const Pontuacao & rhs);
}
#endif
