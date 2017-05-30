#pragma once

#include "peca/Peca.h"
#include "peca/Tabuleiro.h"

namespace peca {
namespace mck {

Peca criaPecaSequencialCrescente(unsigned char cor0);
Peca criaPecaSequencialDecrescente(unsigned char cor0);
void printPeca(const std::string & file,
               int line,
               const Peca & peca);
void printTabuleiro(const std::string & file,
                    int line,
                    const Tabuleiro & tabuleiro);

}
}
