#pragma once

#include "game/State.h"
#include "grafico/Janela.h"

#include <cstdint>

namespace grafico {

/** Responsável por desenhar o tabuleiro. */
class DesenhaTabuleiro {
public:
    /**
     * @param left                  o X onde será mostrado o tabuleiro
     * @param top                   o Y onde será mostrado o tabuleiro
     * @param tamanhoQuadradinho    o tamanho do quadradinho em pixels
     * @param stepQuadradinho       o tamanho do passo dentro do quadradinho
     */
    DesenhaTabuleiro(uint16_t left,
          uint16_t top,
          uint16_t tamanhoQuadradinho,
          uint16_t stepQuadradinho);
    /** Desenha o tabuleiro na tela.
     * @param janela        a janela onde será desenhado o tabuleiro
     * @param sit           a situação do game
     * @param corEliminacao a cor para pintar as peças durante a elimintação
     */
    void desenha(Janela& janela,
          const game::State& sit,
          const gui::Color& corEliminacao) const;

private:
    uint16_t left_;               ///< o X onde será mostrado o tabuleiro
    uint16_t top_;                ///< o Y onde será mostrado o tabuleiro
    uint16_t tamanhoQuadradinho_; ///< o tamanho do quadradinho em pixels
    uint16_t stepQuadradinho_;    ///< o tamanho do passo dentro do quadradinho
    /** Desenha o tabuleiro na tela.
     * @param janela    a janela onde será desenhado o tabuleiro
     * @param tab       o tabuleiro sendo desenhado
     */
    void desenha(Janela& janela,
          const piece::Board& tab) const;

    /** Desenha o quadrado na tela.
     * @param janela    a janela onde será desenhado o tabuleiro
     * @param cor       a cor do quadradinho
     * @param coluna    a coluna no tabuleiro
     * @param linha     a linha no tabuleiro
     * @param sublinha  a sublinha no tabuleiro (peça caindo)
     */
    void desenhaQuadrado(Janela& janela,
          const gui::Color& cor,
          uint16_t coluna,
          uint16_t linha,
          uint16_t sublinha = 0) const;
};
}
