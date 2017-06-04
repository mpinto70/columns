#pragma once

#include "pontuacao/Pontuacao.h"

namespace pontuacao {
/** Respons�vel armazenar e processar um placar (recorde/pontos). */
class Placar {
public:
    /**
     * @param recorde   o recorde
     * @param pontos    a pontua��o inicial
     */
    Placar(const Pontuacao& recorde = Pontuacao(0),
           const Pontuacao& pontos = Pontuacao(0));
    const Pontuacao& recorde() const { return recorde_; }
    const Pontuacao& pontuacao() const { return pontuacao_; }
    /** Acrescenta pontos ao total da pontua��o corrente.
     * @param n a quantidade de pe�as que foram unidas e sumiram
     */
    void acrescenta(size_t n);
    void zera();
private:
    Pontuacao recorde_;     ///< o recorde
    Pontuacao pontuacao_;   ///< a pontua��o
};

bool operator == (const Placar& lhs, const Placar& rhs);
bool operator != (const Placar& lhs, const Placar& rhs);
}
