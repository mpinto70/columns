#pragma once

#include "piece/Board.h"
#include "piece/Creator.h"
#include "piece/Piece.h"
#include "piece/Position.h"

#include <memory>

namespace piece {
bool operator!=(const Piece& lhs, const Piece& rhs);

bool operator==(const Board& lhs, const Board& rhs);
bool operator!=(const Board& lhs, const Board& rhs);

bool operator!=(const Board::Tile& lhs, const Board::Tile& rhs);

bool operator==(const Position& lhs, const Position& rhs);
bool operator!=(const Position& lhs, const Position& rhs);

namespace mck {

Piece create_piece_step(gui::Color color0, char step_size);
Piece create_piece_step(unsigned char color0, char step_size);
Piece create_piece_ascending(unsigned char color0);
Piece create_piece_descending(unsigned char color0);

CreatorPtr create_cycle_creator(
      const std::vector<piece::Piece>& cycle,
      const std::vector<size_t>& columns);

std::unique_ptr<Board> dup(const Board& rhs);
void fix(Board& board, const Piece& piece, const Position& position);
void fill_column(Board& board, size_t column, size_t first_row);
void fill_board(Board& board, size_t first_row);

void print_piece(const std::string& file, int line, const Piece& piece);
void print_board(const std::string& file, int line, const Board& board);
} // namespace mck
} // namespace piece
