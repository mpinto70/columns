#pragma once

#include "piece/Board.h"
#include "piece/Piece.h"

namespace piece {
namespace mck {

Piece create_piece_ascending(unsigned char color0);
Piece create_piece_descending(unsigned char color0);
void print_piece(const std::string& file,
      int line,
      const Piece& piece);
void print_board(const std::string& file,
      int line,
      const Board& board);
}
}
