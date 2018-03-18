
#include "utilpeca.h"
#include "../mck/gui/utilgui.h"

#include <cstdio>
#include <string>

namespace peca {
namespace mck {

static Tile criaPecaSequencialPasso(unsigned char cor0,
      char passo) {
    std::vector<gui::Color> cores;
    unsigned char cor = cor0;
    for (unsigned char i = 0; i < TILE_SIZE; ++i) {
        gui::Color rgb(cor, cor, cor);
        cores.push_back(rgb);
        cor += passo;
    }
    return Tile(cores);
}

Tile criaPecaSequencialCrescente(unsigned char cor0) {
    return criaPecaSequencialPasso(cor0, 1);
}

Tile criaPecaSequencialDecrescente(unsigned char cor0) {
    return criaPecaSequencialPasso(cor0, -1);
}

void printPeca(const std::string& file,
      int line,
      const Tile& peca) {
    printf("Imprimindo peca de %s(%d)\n", file.c_str(), line);
    const std::string sep(TILE_SIZE * 11, '-');
    printf("%s\n", sep.c_str());
    for (unsigned char c = 0; c < TILE_SIZE; ++c) {
        const gui::Color& cor = peca[c];
        gui::mck::print(cor);
    }
    printf("\n");
    printf("%s\n\n", sep.c_str());
}

void printTabuleiro(const std::string& file,
      const int line,
      const Tabuleiro& tabuleiro) {
    printf("Imprimindo tabuleiro de %s(%d)\n", file.c_str(), line);
    const std::string sep(tabuleiro.largura() * 11, '-');
    printf("%s\n", sep.c_str());
    for (uint16_t l = 0; l < tabuleiro.altura(); ++l) {
        for (uint16_t c = 0; c < tabuleiro.largura(); ++c) {
            const gui::Color& cor = tabuleiro.at(c, l);
            gui::mck::print(cor);
        }
        printf("\n");
    }
    printf("%s\n\n", sep.c_str());
}
}
}
