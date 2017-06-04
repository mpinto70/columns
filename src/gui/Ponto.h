#pragma once

#include <cstdint>
#include <utility>

namespace gui {
using namespace std::rel_ops;

/** Respons�vel por representar um ponto 2D. */
struct Ponto {
    /** Cria um ponto na origem. */
    constexpr Ponto()
        : X(0),
          Y(0) {
    }
    /**
     * @param x a coordenada x
     * @param y a coordenada y
     */
    constexpr Ponto(uint16_t x,
                    uint16_t y)
        : X(x),
          Y(y) {
    }
    void swap(Ponto& rhs);
    uint16_t X; ///< a posi��o x
    uint16_t Y; ///< a posi��o y
};

bool operator == (const Ponto& lhs, const Ponto& rhs);
bool operator != (const Ponto& lhs, const Ponto& rhs);

}
