#pragma once

#include "grafico/Janela.h"
#include <SDL2/SDL.h>
#include <unistd.h>

/** namespace das entidades relacionadas à biblioteca gráfica. */
namespace grafico {

/** Responsável por gerenciar a janela. */
class JanelaSDL : public Janela {
public:
    /** Cria o objeto informando onde é o canto superior esquerdo, a largura
     * e a altura da janela em pixels
     * @param nome      o nome da aplicação
     * @param left      o X onde será mostrado a janela
     * @param top       o Y onde será mostrado a janela
     * @param width     a largura da janela
     * @param height    a altura da janela
     * @param cor       a cor de fundo da janela
     */
    JanelaSDL(const std::string& nome,
          uint16_t left,
          uint16_t top,
          uint16_t width,
          uint16_t height,
          const gui::Cor& cor);
    /** Destrói a janela. */
    ~JanelaSDL() override;
    /** @return a janela para desenho. */
    SDL_Window& window() const { return *window_; }
    /** @return o renderer. */
    SDL_Renderer& renderer() { return *renderer_; }
    /** limpa a janela. */
    void limpa() override;
    /** mostra a janela. */
    void atualiza() override;

private:
    SDL_Window* window_;     ///< a janela
    SDL_Renderer* renderer_; ///< o renderer de imagens
    gui::Cor cor_;           ///< a cor de fundo da janela
    /** desenha uma linha.
     * @param x1    coordenada x do ponto inicial
     * @param y1    coordenada y do ponto inicial
     * @param x2    coordenada x do ponto final
     * @param y2    coordenada y do ponto final
     * @param cor   cor
     */
    void linha_(uint16_t x1,
          uint16_t y1,
          uint16_t x2,
          uint16_t y2,
          const gui::Cor& cor) override;
    /** desenha um retângulo.
     * @param x1    coordenada x do canto superior esquerdo
     * @param y1    coordenada y do canto superior esquerdo
     * @param x2    coordenada x do canto inferior direito
     * @param y2    coordenada y do canto inferior direito
     * @param cor   cor
     */
    void retangulo_(uint16_t x1,
          uint16_t y1,
          uint16_t x2,
          uint16_t y2,
          const gui::Cor& cor) override;
    /** preenche um retângulo.
     * @param x1    coordenada x do canto superior esquerdo
     * @param y1    coordenada y do canto superior esquerdo
     * @param x2    coordenada x do canto inferior direito
     * @param y2    coordenada y do canto inferior direito
     * @param cor   cor
     */
    void preenche_(uint16_t x1,
          uint16_t y1,
          uint16_t x2,
          uint16_t y2,
          const gui::Cor& cor) override;
    /** escreve um texto.
     * @param texto o texto a ser escrito
     * @param x     coordenada x do ponto de escrita
     * @param y     coordenada y do ponto de escrita
     * @param fonte a fonte
     * @param cor   a cor
     * @returns o retângulo que envolve o texto
     */
    gui::Retangulo escreve_(const std::string& texto,
          uint16_t x,
          uint16_t y,
          const gui::Fonte& fonte,
          const gui::Cor& cor) override;
};
}
