#pragma once

#include "piece/Board.h"
#include "piece/Piece.h"

namespace piece {
namespace mck {

Piece criaPecaSequencialCrescente(unsigned char cor0);
Piece criaPecaSequencialDecrescente(unsigned char cor0);
void printPeca(const std::string& file,
      int line,
      const Piece& piece);
void printTabuleiro(const std::string& file,
      int line,
      const Board& tabuleiro);
}
}
