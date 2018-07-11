#include "utilpiece.h"

#include "../mck/gui/utilgui.h"

#include "CreatorCycle.h"

#include <cstdio>
#include <string>

namespace piece {
bool operator!=(const Piece& lhs, const Piece& rhs) {
    return not(lhs == rhs);
}

bool operator==(const Board& lhs, const Board& rhs) {
    return lhs.height() == rhs.height()
           && lhs.width() == rhs.width()
           && lhs.tiles() == rhs.tiles();
}

bool operator!=(const Board& lhs, const Board& rhs) {
    return not(lhs == rhs);
}

bool operator!=(const Board::Tile& lhs, const Board::Tile& rhs) {
    return not(lhs == rhs);
}

bool operator==(const Position& lhs, const Position& rhs) {
    return lhs.column() == rhs.column()
           && lhs.row() == rhs.row()
           && lhs.sub_row() == rhs.sub_row();
}

bool operator!=(const Position& lhs, const Position& rhs) {
    return not(lhs == rhs);
}

namespace mck {

Piece create_piece_step(gui::Color color0, char step_size) {
    return create_piece_step(static_cast<int>(color0), step_size);
}

Piece create_piece_step(unsigned char color0, char step_size) {
    gui::Color colors[PIECE_SIZE];
    unsigned char color = color0;
    for (unsigned char i = 0; i < PIECE_SIZE; ++i) {
        const size_t color_index = color % gui::mck::end_color();
        const gui::Color cr = ::gui::mck::to_color(color_index);
        colors[i] = cr;
        color += step_size;
    }
    return Piece(colors);
}

Piece create_piece_ascending(unsigned char color0) {
    return create_piece_step(color0, 1);
}

Piece create_piece_descending(unsigned char color0) {
    return create_piece_step(color0, -1);
}

CreatorPtr create_cycle_creator(const std::vector<piece::Piece>& cycle,
      const std::vector<size_t>& columns) {
    return std::make_unique<CreatorCycle>(cycle, columns);
}

std::unique_ptr<Board> dup(const Board& rhs) {
    auto other = std::make_unique<Board>(rhs.width(), rhs.height());
    for (size_t r = 0; r < rhs.height(); ++r) {
        for (size_t c = 0; c < rhs.width(); ++c) {
            other->at(c, r) = rhs.at(c, r);
        }
    }
    return std::move(other);
}

void fix(Board& board, const Piece& piece, const Position& position) {
    const size_t column = position.column();
    for (size_t i = 0; i < piece::PIECE_SIZE; ++i) {
        board.at(column, position.row() + i) = piece[i];
    }
}

void fill_column(Board& board, size_t column, size_t first_row) {
    if (column >= board.width())
        throw std::runtime_error("fill - invalid column");
    for (size_t r = first_row; r < board.height(); ++r) {
        board.at(column, r) = gui::Color::BLUE;
    }
}

void fill_board(Board& board, size_t first_row) {
    for (size_t c = 0; c < board.width(); ++c) {
        fill_column(board, c, first_row);
    }
}

void print_piece(const std::string& file,
      int line,
      const Piece& piece) {
    printf("Printing piece from %s(%d)\n", file.c_str(), line);
    const std::string separator(PIECE_SIZE * 11, '-');
    printf("%s\n", separator.c_str());
    for (unsigned char c = 0; c < PIECE_SIZE; ++c) {
        gui::Color color = piece[c];
        gui::mck::print(color);
    }
    printf("\n");
    printf("%s\n\n", separator.c_str());
}

void print_board(const std::string& file,
      const int line,
      const Board& board) {
    printf("Printing board from %s(%d)\n", file.c_str(), line);
    const std::string separator(board.width() * 11, '-');
    printf("%s\n", separator.c_str());
    for (size_t l = 0; l < board.height(); ++l) {
        for (size_t c = 0; c < board.width(); ++c) {
            gui::Color color = board.at(c, l);
            gui::mck::print(color);
        }
        printf("\n");
    }
    printf("%s\n\n", separator.c_str());
}
}
}
