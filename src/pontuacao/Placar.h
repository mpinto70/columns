#pragma once

#include "pontuacao/Pontuacao.h"

namespace pontuacao {
/** Responsável armazenar e processar um placar (recorde/pontos). */
class Placar {
public:
    /**
     * @param recorde   o recorde
     * @param pontos    a pontuação inicial
     */
    Placar(const Pontuacao& recorde = Pontuacao(0),
           const Pontuacao& pontos = Pontuacao(0));
    const Pontuacao& recorde() const { return recorde_; }
    const Pontuacao& pontuacao() const { return pontuacao_; }
    /** Acrescenta pontos ao total da pontuação corrente.
     * @param n a quantidade de peças que foram unidas e sumiram
     */
    void acrescenta(size_t n);
    void zera();
private:
    Pontuacao recorde_;     ///< o recorde
    Pontuacao pontuacao_;   ///< a pontuação
};

bool operator == (const Placar& lhs, const Placar& rhs);
bool operator != (const Placar& lhs, const Placar& rhs);
}
