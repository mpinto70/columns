
#pragma once

namespace gui {

/** Responsável por representar uma cor de 256 níveis para vermelho, verde e azul. */
struct Cor {
    /** Cria uma cor preta. */
    constexpr Cor()
          : R(0),
            G(0),
            B(0) {
    }
    /**
     * @param r a intensidade do vermelho [0 - 255]
     * @param g a intensidade do verde [0 - 255]
     * @param b a intensidade do azul [0 - 255]
     */
    constexpr Cor(unsigned char r,
          unsigned char g,
          unsigned char b)
          : R(r),
            G(g),
            B(b) {
    }
    unsigned char R; ///< a intensidade de vermelho [0 - 255]
    unsigned char G; ///< a intensidade de verde [0 - 255]
    unsigned char B; ///< a intensidade de azul [0 - 255]
};

bool operator==(const Cor& lhs, const Cor& rhs);
bool operator!=(const Cor& lhs, const Cor& rhs);

/** @return a cor passada escurecida em \b percentual%.
 * @param cor a cor base
 * @param percentual o percentual de escurecimento
 */
Cor escurece(Cor cor,
      unsigned char percentual);

constexpr Cor Vermelho{ 255, 0, 0 };    ///< vermelho
constexpr Cor Verde{ 0, 255, 0 };       ///< verde
constexpr Cor Azul{ 0, 0, 255 };        ///< azul
constexpr Cor Branco{ 255, 255, 255 };  ///< branco
constexpr Cor Preto{ 0, 0, 0 };         ///< preto
constexpr Cor Cinza{ 127, 127, 127 };   ///< cinza
constexpr Cor Amarelo{ 255, 255, 0 };   ///< amarelo
constexpr Cor Lavanda{ 153, 102, 255 }; ///< lavanda
}
