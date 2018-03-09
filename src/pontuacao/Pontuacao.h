#pragma once

#include <cstdio>

namespace pontuacao {
/** Respons�vel armazenar e processar a pontua��o. */
class Pontuacao {
public:
    /**
     * @param total a pontua��o inicial
     */
    Pontuacao(size_t total = 0);
    size_t total() const { return total_; }
    /** Acrescenta pontos ao total devido � jun��o de \p n pe�as.
     * @param n a quantidade de pe�as que foram unidas e sumiram
     */
    void acrescenta(size_t n);
    void zera() { total_ = 0; }

private:
    size_t total_; ///< a pontua��o
};

bool operator==(const Pontuacao& lhs, const Pontuacao& rhs);
bool operator!=(const Pontuacao& lhs, const Pontuacao& rhs);
bool operator<(const Pontuacao& lhs, const Pontuacao& rhs);
}
