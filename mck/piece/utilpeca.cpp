
#include "utilpeca.h"
#include "../mck/gui/utilgui.h"

#include <cstdio>
#include <string>

namespace piece {
namespace mck {

static Piece criaPecaSequencialPasso(unsigned char cor0,
      char passo) {
    std::vector<gui::Color> cores;
    unsigned char cor = cor0;
    for (unsigned char i = 0; i < PIECE_SIZE; ++i) {
        gui::Color rgb(cor, cor, cor);
        cores.push_back(rgb);
        cor += passo;
    }
    return Piece(cores);
}

Piece criaPecaSequencialCrescente(unsigned char cor0) {
    return criaPecaSequencialPasso(cor0, 1);
}

Piece criaPecaSequencialDecrescente(unsigned char cor0) {
    return criaPecaSequencialPasso(cor0, -1);
}

void printPeca(const std::string& file,
      int line,
      const Piece& piece) {
    printf("Imprimindo piece de %s(%d)\n", file.c_str(), line);
    const std::string sep(PIECE_SIZE * 11, '-');
    printf("%s\n", sep.c_str());
    for (unsigned char c = 0; c < PIECE_SIZE; ++c) {
        const gui::Color& cor = piece[c];
        gui::mck::print(cor);
    }
    printf("\n");
    printf("%s\n\n", sep.c_str());
}

void printTabuleiro(const std::string& file,
      const int line,
      const Board& tabuleiro) {
    printf("Imprimindo tabuleiro de %s(%d)\n", file.c_str(), line);
    const std::string sep(tabuleiro.width() * 11, '-');
    printf("%s\n", sep.c_str());
    for (uint16_t l = 0; l < tabuleiro.height(); ++l) {
        for (uint16_t c = 0; c < tabuleiro.width(); ++c) {
            const gui::Color& cor = tabuleiro.at(c, l);
            gui::mck::print(cor);
        }
        printf("\n");
    }
    printf("%s\n\n", sep.c_str());
}
}
}
