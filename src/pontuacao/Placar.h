#pragma once

#include "pontuacao/Score.h"

namespace pontuacao {
/** Respons�vel armazenar e processar um placar (recorde/pontos). */
class Placar {
public:
    /**
     * @param recorde   o recorde
     * @param pontos    a pontua��o inicial
     */
    Placar(const Score& recorde = Score(0),
          const Score& pontos = Score(0));
    const Score& recorde() const { return recorde_; }
    const Score& pontuacao() const { return pontuacao_; }
    /** Acrescenta pontos ao total da pontua��o corrente.
     * @param n a quantidade de pe�as que foram unidas e sumiram
     */
    void acrescenta(size_t n);
    void zera();

private:
    Score recorde_;   ///< o recorde
    Score pontuacao_; ///< a pontua��o
};

bool operator==(const Placar& lhs, const Placar& rhs);
bool operator!=(const Placar& lhs, const Placar& rhs);
}
