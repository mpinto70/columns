#pragma once

#include "game/Canvas.h"
#include "graphics/SDL/WindowSDL.h"
#include "gui/Font.h"

#include <SDL2/SDL.h>

namespace graphics {
namespace sdl {
class Canvas : public game::Canvas {
public:
    Canvas(const piece::Board& board,
          const std::string& name,
          int left,
          int top,
          const gui::Font& font_name,
          const gui::Font& font_score);
    ~Canvas() override;

private:
    WindowSDL window_;
    std::string name_;
    gui::Font font_name_;
    gui::Font font_score_;
    int board_width_;
    int board_height_;
    int score_left_;

    void start() override;
    void draw_(const piece::Board& board) override;
    void draw_(const piece::Piece& piece, const piece::Position& piece_position) override;
    void draw_next_(const piece::Piece& next_piece) override;
    void draw_(const state::ScoreBoard& score_board) override;
    void draw_(const piece::Board::EliminationList& elimination_list) override;
    void finish() override;
};
}
}
