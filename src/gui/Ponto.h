
#ifndef PONTO_H_mhpa
#define PONTO_H_mhpa

#include <cstdint>

namespace gui {

/** Responsável por representar um ponto 2D. */
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
    /** Substitui o conteúdo do objeto atual pelo conteúdo de outro objeto.
     * @param rhs o outro objeto
     */
    void swap(Ponto & rhs);
    uint16_t X; ///< a posição x
    uint16_t Y; ///< a posição y
};

/** @return se os dois pontos são o mesmo.
 * @param lhs o objeto à esquerda do operador
 * @param rhs o objeto à direita do operador
 */
bool operator == (const Ponto & lhs, const Ponto & rhs);

}
#endif
