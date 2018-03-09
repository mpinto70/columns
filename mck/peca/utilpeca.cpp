
#include "utilpeca.h"
#include "../mck/gui/utilgui.h"

#include <cstdio>
#include <string>

namespace peca {
namespace mck {

static Peca criaPecaSequencialPasso(unsigned char cor0,
      char passo) {
    std::vector<gui::Cor> cores;
    unsigned char cor = cor0;
    for (unsigned char i = 0; i < TAMANHO_PECA; ++i) {
        gui::Cor rgb(cor, cor, cor);
        cores.push_back(rgb);
        cor += passo;
    }
    return Peca(cores);
}

Peca criaPecaSequencialCrescente(unsigned char cor0) {
    return criaPecaSequencialPasso(cor0, 1);
}

Peca criaPecaSequencialDecrescente(unsigned char cor0) {
    return criaPecaSequencialPasso(cor0, -1);
}

void printPeca(const std::string& file,
      int line,
      const Peca& peca) {
    printf("Imprimindo peca de %s(%d)\n", file.c_str(), line);
    const std::string sep(TAMANHO_PECA * 11, '-');
    printf("%s\n", sep.c_str());
    for (unsigned char c = 0; c < TAMANHO_PECA; ++c) {
        const gui::Cor& cor = peca[c];
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
            const gui::Cor& cor = tabuleiro.at(c, l);
            gui::mck::print(cor);
        }
        printf("\n");
    }
    printf("%s\n\n", sep.c_str());
}
}
}
