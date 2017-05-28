
#ifndef PONTO_H_mhpa
#define PONTO_H_mhpa

#include <cstdint>

namespace gui {

/** Respons�vel por representar um ponto 2D. */
struct Ponto {
    /** Cria um ponto na origem. */
    constexpr Ponto()
        : X(0),
          Y(0) {
    }
    /** Cria um ponto informando as coordenadas.
     * @param x a coordenada x
     * @param y a coordenada y
     */
    constexpr Ponto(uint16_t x,
                    uint16_t y)
        : X(x),
          Y(y) {
    }
    /** Substitui o conte�do do objeto atual pelo conte�do de outro objeto.
     * @param rhs o outro objeto
     */
    void swap(Ponto & rhs);
    uint16_t X; ///< a posi��o x
    uint16_t Y; ///< a posi��o y
};

/** @return se os dois pontos s�o o mesmo.
 * @param lhs o objeto � esquerda do operador
 * @param rhs o objeto � direita do operador
 */
bool operator == (const Ponto & lhs, const Ponto & rhs);

}
#endif
