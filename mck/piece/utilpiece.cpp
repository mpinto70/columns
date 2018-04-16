#include "utilpiece.h"

#include "../mck/gui/utilgui.h"

#include <cstdio>
#include <string>

namespace piece {
bool operator==(const Piece& lhs, const Piece& rhs) {
    return std::equal(lhs.colors_, lhs.colors_ + PIECE_SIZE, rhs.colors_);
}

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

bool operator==(const PiecePosition& lhs, const PiecePosition& rhs) {
    return lhs.column() == rhs.column()
           && lhs.row() == rhs.row()
           && lhs.sub_row() == rhs.sub_row()
           && lhs.max_sub_row() == rhs.max_sub_row();
}

bool operator!=(const PiecePosition& lhs, const PiecePosition& rhs) {
    return not(lhs == rhs);
}

namespace mck {

static Piece create_piece_step(unsigned char color0, char step_size) {
    std::vector<gui::Color> colors;
    unsigned char color = color0;
    for (unsigned char i = 0; i < PIECE_SIZE; ++i) {
        const size_t color_index = color % gui::mck::end_color();
        gui::Color cr = ::gui::mck::to_color(color_index);
        colors.push_back(cr);
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
