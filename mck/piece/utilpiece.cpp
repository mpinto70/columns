#include "utilpiece.h"

#include "../mck/gui/utilgui.h"

#include <cstdio>
#include <string>

namespace piece {
namespace mck {

static Piece create_piece_step(unsigned char color0, char step_size) {
    std::vector<gui::Color> cores;
    unsigned char color = color0;
    for (unsigned char i = 0; i < PIECE_SIZE; ++i) {
        gui::Color rgb(color, color, color);
        cores.push_back(rgb);
        color += step_size;
    }
    return Piece(cores);
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
        const gui::Color& color = piece[c];
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
    for (uint16_t l = 0; l < board.height(); ++l) {
        for (uint16_t c = 0; c < board.width(); ++c) {
            const gui::Color& color = board.at(c, l);
            gui::mck::print(color);
        }
        printf("\n");
    }
    printf("%s\n\n", separator.c_str());
}
}
}
