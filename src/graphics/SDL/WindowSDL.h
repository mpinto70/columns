#pragma once

#include <SDL2/SDL.h>
#include <unistd.h>

#include <array>
#include <string>

namespace graphics {

using ColorTripletT = std::array<Uint8, 3>;

class WindowSDL {
public:
    WindowSDL(
          const std::string& name,
          size_t left,
          size_t top,
          size_t width,
          size_t height,
          const ColorTripletT& color);

    WindowSDL(const WindowSDL&) = delete;
    WindowSDL& operator=(const WindowSDL&) = delete;
    WindowSDL(WindowSDL&&) = delete;
    WindowSDL& operator=(WindowSDL&&) = delete;

    void clear();

    void update();

    void line(int x1, int y1, int x2, int y2, const ColorTripletT& color);

    void rectangle(const SDL_Rect& rect, const ColorTripletT& color);

    void fill(const SDL_Rect& rect, const ColorTripletT& color);

    SDL_Rect write(
          const std::string& text,
          int x,
          int y,
          const std::string& font_name,
          int font_size,
          const ColorTripletT& color);

private:
    size_t width_;
    size_t height_;
    SDL_Window* window_;
    SDL_Renderer* renderer_;
    ColorTripletT color_;
};
} // namespace graphics
