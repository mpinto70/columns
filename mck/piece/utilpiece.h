#pragma once

#include "piece/Board.h"
#include "piece/Piece.h"
#include "piece/PiecePosition.h"

#include <memory>

namespace piece {
bool operator==(const Piece& lhs, const Piece& rhs);
bool operator!=(const Piece& lhs, const Piece& rhs);

bool operator==(const Board& lhs, const Board& rhs);
bool operator!=(const Board& lhs, const Board& rhs);

bool operator!=(const Board::Tile& lhs, const Board::Tile& rhs);

bool operator==(const PiecePosition& lhs, const PiecePosition& rhs);
bool operator!=(const PiecePosition& lhs, const PiecePosition& rhs);

namespace mck {

Piece create_piece_step(unsigned char color0, char step_size);
Piece create_piece_ascending(unsigned char color0);
Piece create_piece_descending(unsigned char color0);

std::unique_ptr<Board> dup(const Board& rhs);
void fix(Board& board, const Piece& piece, const PiecePosition& position);

void print_piece(const std::string& file,
      int line,
      const Piece& piece);
void print_board(const std::string& file,
      int line,
      const Board& board);
}
}
