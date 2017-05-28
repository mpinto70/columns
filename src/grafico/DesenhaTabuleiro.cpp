
#include "DesenhaTabuleiro.h"

namespace grafico {

/** Desenha o quadradinho.
    @param janela a janela onde será desenhado o quadradinho
    @param cor a cor do quadradinho
    @param x1 o X no canvas do canto superior esquerdo do quadradinho
    @param y1 o Y no canvas do canto superior esquerdo do quadradinho
    @param tamanho o tamanho do quadradinho em pixels
 */
static void pintaQuadrado(Janela & janela,
                          const gui::Cor & cor,
                          const uint16_t x1,
                          const uint16_t y1,
                          const uint16_t tamanho) {
    const int x2 = x1 + tamanho - 1;
    const int y2 = y1 + tamanho - 1;
    janela.preenche(gui::Retangulo(x1, y1, x2, y2), cor);
    /*
    const auto corfundo = converteCor(gui::escurece(cor, 80));
    canvas.draw_line(x2 - 0, y1 + 0, x2 - 0, y2 - 0, corfundo); // linha vertical em x2
    canvas.draw_line(x2 - 1, y1 + 1, x2 - 1, y2 - 0, corfundo); // linha vertical em x2 - 1
    canvas.draw_line(x1 + 1, y2 - 0, x2 - 2, y2 - 0, corfundo); // linha horizontal em y2
    canvas.draw_line(x1 + 2, y2 - 1, x2 - 2, y2 - 1, corfundo); // linha horizontal em y2 - 1

    const auto cortopo = converteCor(gui::escurece(cor, 40));
    canvas.draw_line(x1 + 0, y1 + 0, x1 + 0, y2 - 0, cortopo); // linha vertical em x1
    canvas.draw_line(x1 + 1, y1 + 0, x1 + 1, y2 - 1, cortopo); // linha vertical em x1 + 1
    canvas.draw_line(x1 + 2, y1 + 0, x2 - 1, y1 + 0, cortopo); // linha horizontal em y1
    canvas.draw_line(x1 + 2, y1 + 1, x2 - 2, y1 + 1, cortopo); // linha horizontal em y1 + 1
    */
}

DesenhaTabuleiro::DesenhaTabuleiro(const uint16_t left,
                                   const uint16_t top,
                                   const uint16_t tamanhoQuadradinho,
                                   const uint16_t stepQuadradinho)
    : left_(left),
      top_(top),
      tamanhoQuadradinho_(tamanhoQuadradinho),
      stepQuadradinho_(stepQuadradinho) {
    if (tamanhoQuadradinho == 0)
        throw std::invalid_argument("DesenhaTabuleiro - tamanho nulo");
    if (stepQuadradinho == 0)
        throw std::invalid_argument("DesenhaTabuleiro - passo interno nulo");
    if (tamanhoQuadradinho % stepQuadradinho != 0)
        throw std::invalid_argument("DesenhaTabuleiro - relação inválida entre os tamanhos do quadradinho e do step");
}

void DesenhaTabuleiro::desenha(Janela & janela,
                               const jogo::Situacao & sit,
                               const gui::Cor & corEliminacao) const {
    desenha(janela, sit.tabuleiro());
    if (sit.temPeca()) {
        const auto & posic = sit.posicaoPeca();
        const auto & peca = sit.peca();
        for (uint16_t i = 0; i < peca::TAMANHO_PECA; ++i) {
            desenhaQuadrado(janela, peca[i], posic.coluna(), posic.linha() + i, posic.subLinha());
        }
    } else {
        for (const auto & eliminada : sit.eliminacao()) {
            const auto col = eliminada.first;
            const auto lin = eliminada.second;
            desenhaQuadrado(janela, corEliminacao, col, lin);
        }
    }
}

void DesenhaTabuleiro::desenha(Janela & janela,
                               const peca::Tabuleiro & tab) const {
    janela.preenche(gui::Retangulo(left_,
                                   top_,
                                   left_ + tab.largura() * tamanhoQuadradinho_,
                                   top_ + tab.altura() * tamanhoQuadradinho_),
                    tab.cor());

    for (uint16_t i = 0; i < tab.largura(); ++i) {
        for (uint16_t j = 0; j < tab.altura(); ++j) {
            const auto & corCelula = tab.at(i, j);
            if (corCelula == tab.cor())
                continue; // é fundo
            desenhaQuadrado(janela, corCelula, i, j);
        }
    }
}

void DesenhaTabuleiro::desenhaQuadrado(Janela & janela,
                                       const gui::Cor & cor,
                                       const uint16_t coluna,
                                       const uint16_t linha,
                                       const uint16_t sublinha) const {
    const auto x = coluna * tamanhoQuadradinho_ + left_;
    const auto dy = sublinha * stepQuadradinho_;
    const int y = linha * tamanhoQuadradinho_ + dy + top_;
    pintaQuadrado(janela,
                  cor,
                  x,
                  y,
                  tamanhoQuadradinho_);
}

}
