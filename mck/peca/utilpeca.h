#pragma once

#include "peca/Tabuleiro.h"
#include <peca/Piece.h>

namespace peca {
namespace mck {

Piece criaPecaSequencialCrescente(unsigned char cor0);
Piece criaPecaSequencialDecrescente(unsigned char cor0);
void printPeca(const std::string& file,
      int line,
      const Piece& peca);
void printTabuleiro(const std::string& file,
      int line,
      const Tabuleiro& tabuleiro);
}
}
