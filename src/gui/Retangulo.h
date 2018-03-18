#pragma once

#include "gui/Point.h"

#include <cstdint>

namespace gui {

/** Responsável por representar um retângulo 2D. */
struct Retangulo {
public:
    /**
     * @param x1 a coordenada x de um dos cantos
     * @param y1 a coordenada y de um dos cantos
     * @param x2 a coordenada x do outro canto
     * @param y2 a coordenada y do outro canto
     */
    Retangulo(uint16_t x1,
          uint16_t y1,
          uint16_t x2,
          uint16_t y2);
    /**
     * @param p1 um dos cantos
     * @param p2 o outro canto
     */
    Retangulo(const Point& p1,
          const Point& p2);
    /** @return a cordenada X do canto superior esquerdo. */
    uint16_t X1() const { return X1_; }
    /** @return a cordenada Y do canto superior esquerdo. */
    uint16_t Y1() const { return Y1_; }
    /** @return a cordenada X do canto inferior direito. */
    uint16_t X2() const { return X2_; }
    /** @return a cordenada Y do canto inferior direito. */
    uint16_t Y2() const { return Y2_; }
    /** @return o canto superior esquerdo. */
    Point P1() const { return Point(X1_, Y1_); }
    /** @return o canto inferior direito. */
    Point P2() const { return Point(X2_, Y2_); }

private:
    uint16_t X1_; ///< a posição x
    uint16_t Y1_; ///< a posição y
    uint16_t X2_; ///< a posição x
    uint16_t Y2_; ///< a posição y
};

bool operator==(const Retangulo& lhs, const Retangulo& rhs);
}
