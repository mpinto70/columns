#pragma once

#include "piece/Board.h"
#include "piece/Piece.h"
#include "piece/PiecePosition.h"

namespace piece {
bool operator==(const Piece& lhs, const Piece& rhs);
bool operator!=(const Piece& lhs, const Piece& rhs);

bool operator==(const Board& lhs, const Board& rhs);
bool operator!=(const Board& lhs, const Board& rhs);

bool operator!=(const Board::Tile& lhs, const Board::Tile& rhs);

bool operator==(const PiecePosition& lhs, const PiecePosition& rhs);
bool operator!=(const PiecePosition& lhs, const PiecePosition& rhs);

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
