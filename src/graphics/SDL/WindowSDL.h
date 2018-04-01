#pragma once

#include "graphics/Window.h"

#include <SDL2/SDL.h>
#include <unistd.h>

namespace graphics {

class WindowSDL : public Window {
public:
    WindowSDL(const std::string& name,
          size_t left,
          size_t top,
          size_t width,
          size_t height,
          gui::Color color);
    ~WindowSDL() override;

    SDL_Window& window() const { return *window_; }

    SDL_Renderer& renderer() { return *renderer_; }

    void clear() override;

    void update() override;

private:
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    gui::Color color_;

    void line_(size_t x1,
          size_t y1,
          size_t x2,
          size_t y2,
          gui::Color color) override;

    void rectangle_(size_t x1,
          size_t y1,
          size_t x2,
          size_t y2,
          gui::Color color) override;

    void fill_(size_t x1,
          size_t y1,
          size_t x2,
          size_t y2,
          gui::Color color) override;

    gui::Rectangle write_(const std::string& text,
          size_t x,
          size_t y,
          const gui::Font& fonte,
          gui::Color color) override;

    void draw_(piece::SharedConstBoard board) override;
    void draw_(const piece::Piece& piece, const piece::PiecePosition& piece_position) override;
    void draw_next_(const piece::Piece& next_piece) override;
    void draw_(const state::ScoreBoard& score_board) override;
    void draw_(const state::EliminationList& elimination_list) override;
};
}
