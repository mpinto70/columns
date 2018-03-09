#pragma once

#include <cstdio>

namespace pontuacao {
/** Responsável armazenar e processar a pontuação. */
class Pontuacao {
public:
    /**
     * @param total a pontuação inicial
     */
    Pontuacao(size_t total = 0);
    size_t total() const { return total_; }
    /** Acrescenta pontos ao total devido à junção de \p n peças.
     * @param n a quantidade de peças que foram unidas e sumiram
     */
    void acrescenta(size_t n);
    void zera() { total_ = 0; }

private:
    size_t total_; ///< a pontuação
};

bool operator==(const Pontuacao& lhs, const Pontuacao& rhs);
bool operator!=(const Pontuacao& lhs, const Pontuacao& rhs);
bool operator<(const Pontuacao& lhs, const Pontuacao& rhs);
}
