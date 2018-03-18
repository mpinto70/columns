#pragma once

#include "peca/Tabuleiro.h"
#include <peca/Tile.h>

namespace peca {
namespace mck {

Tile criaPecaSequencialCrescente(unsigned char cor0);
Tile criaPecaSequencialDecrescente(unsigned char cor0);
void printPeca(const std::string& file,
      int line,
      const Tile& peca);
void printTabuleiro(const std::string& file,
      int line,
      const Tabuleiro& tabuleiro);
}
}
