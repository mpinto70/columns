#include "WindowSDL.h"

#include <SDL2/SDL_ttf.h>

#include <stdexcept>

namespace graphics {
namespace {
constexpr Uint8 COLORS[][3] = {
    { 0x98, 0x1b, 0x1e }, // RED
    { 0x2e, 0x85, 0x40 }, // GREEN
    { 0x02, 0xbf, 0xe7 }, // BLUE
    { 0xf1, 0xf1, 0xf1 }, // WHITE
    { 0, 0, 0 },          // BLACK
    { 127, 127, 127 },    // GRAY
    { 0xfd, 0xb8, 0x1e }, // YELLOW
    { 0x4c, 0x2c, 0x92 }, // LAVENDER
};

const Uint8* to_color_triplet(gui::Color color) {
    return COLORS[static_cast<unsigned int>(color)];
}

SDL_Color to_sdl_color(gui::Color color) {
    const auto sdl_color = to_color_triplet(color);
    return SDL_Color{ sdl_color[0], sdl_color[1], sdl_color[2] };
}

SDL_Rect to_sdl_rect(const size_t x1,
      const size_t y1,
      const size_t x2,
      const size_t y2) {
    return { int(x1), int(y1), int(x2 - x1 + 1), int(y2 - y1 + 1) };
}
}

WindowSDL::WindowSDL(const std::string& name,
      const size_t left,
      const size_t top,
      const size_t width,
      const size_t height,
      gui::Color color)
      : Window(name, width, height),
        window_(nullptr),
        renderer_(nullptr),
        color_(color) {
    window_ = SDL_CreateWindow(name.c_str(), left, top, width, height, SDL_WINDOW_SHOWN);
    if (window_ == nullptr) {
        throw std::runtime_error("WindowSDL - error creating window: " + std::string(SDL_GetError()));
    }
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer_ == nullptr) {
        throw std::runtime_error("WindowSDL - error creating renderer: " + std::string(SDL_GetError()));
    }
}

WindowSDL::~WindowSDL() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
}

void WindowSDL::clear() {
    const auto sdl_color = to_color_triplet(color_);
    if (SDL_SetRenderDrawColor(renderer_, sdl_color[0], sdl_color[1], sdl_color[2], SDL_ALPHA_OPAQUE) != 0) {
        throw std::runtime_error("WindowSDL::clear - SDL_SetRenderDrawColor error");
    }
    if (SDL_RenderClear(renderer_) != 0) {
        throw std::runtime_error("WindowSDL::clear - SDL_RenderClear error");
    }
}

void WindowSDL::update() {
    SDL_RenderPresent(renderer_);
}

void WindowSDL::line_(const size_t x1,
      const size_t y1,
      const size_t x2,
      const size_t y2,
      gui::Color color) {
    const auto sdl_color = to_color_triplet(color);
    if (SDL_SetRenderDrawColor(renderer_, sdl_color[0], sdl_color[1], sdl_color[2], SDL_ALPHA_OPAQUE) != 0) {
        throw std::runtime_error("WindowSDL::linha_ - erro no SDL_SetRenderDrawColor");
    }

    if (SDL_RenderDrawLine(renderer_, x1, y1, x2, y2) != 0) {
        throw std::runtime_error("WindowSDL::linha_ - erro no SDL_RenderDrawLine");
    }
}

void WindowSDL::rectangle_(const size_t x1,
      const size_t y1,
      const size_t x2,
      const size_t y2,
      gui::Color color) {
    const SDL_Rect rect = to_sdl_rect(x1, y1, x2, y2);
    const auto sdl_color = to_color_triplet(color);
    if (SDL_SetRenderDrawColor(renderer_, sdl_color[0], sdl_color[1], sdl_color[2], SDL_ALPHA_OPAQUE) != 0) {
        throw std::runtime_error("WindowSDL::retangulo_ - erro no SDL_SetRenderDrawColor");
    }
    if (SDL_RenderDrawRect(renderer_, &rect)) {
        throw std::runtime_error("WindowSDL::retangulo_ - erro no SDL_RenderDrawRect");
    }
}

void WindowSDL::fill_(const size_t x1,
      const size_t y1,
      const size_t x2,
      const size_t y2,
      gui::Color color) {
    const SDL_Rect rect = to_sdl_rect(x1, y1, x2, y2);
    const auto sdl_color = to_color_triplet(color);
    if (SDL_SetRenderDrawColor(renderer_, sdl_color[0], sdl_color[1], sdl_color[2], SDL_ALPHA_OPAQUE) != 0) {
        throw std::runtime_error("WindowSDL::preenche_ - erro no SDL_SetRenderDrawColor");
    }
    if (SDL_RenderFillRect(renderer_, &rect) != 0) {
        throw std::runtime_error("WindowSDL::preenche_ - erro no SDL_RenderFillRect");
    }
}

gui::Rectangle WindowSDL::write_(const std::string& text,
      const size_t x,
      const size_t y,
      const gui::Font& fonte,
      gui::Color color) {
    TTF_Font* font = nullptr;
    SDL_Surface* surface = nullptr;
    SDL_Texture* texture = nullptr;
    gui::Rectangle res(0, 0, 0, 0);
    try {
        const SDL_Color sdl_color = to_sdl_color(color);
        font = TTF_OpenFont(fonte.name().c_str(), fonte.size());
        if (font == nullptr) {
            throw std::runtime_error("WindowSDL::write_ - opening font " + fonte.name());
        }

        //We need to first render to a surface as that's what TTF_RenderText
        //returns, then load that surface into a texture
        surface = TTF_RenderText_Blended(font, text.c_str(), sdl_color);
        if (surface == nullptr) {
            throw std::runtime_error("WindowSDL::write_ - getting the surface " + text);
        }

        texture = SDL_CreateTextureFromSurface(renderer_, surface);
        if (texture == nullptr) {
            throw std::runtime_error("WindowSDL::write_ - getting the texture");
        }

        //Get the texture w/h so we can center it in the screen
        SDL_Rect dst;
        dst.x = x;
        dst.y = y;
        //Query the texture to get its width and height to use
        if (SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h) != 0) {
            throw std::runtime_error("WindowSDL::write_ - SDL_QueryTexture error");
        }

        res = gui::Rectangle(x, y, x + dst.w, y + dst.h);
        if (SDL_RenderCopy(renderer_, texture, nullptr, &dst) != 0) {
            throw std::runtime_error("WindowSDL::write_ - SDL_RenderCopy error");
        }
    } catch (...) {
        //Clean up the surface and font
        if (surface != nullptr) {
            SDL_FreeSurface(surface);
        }
        if (font != nullptr) {
            TTF_CloseFont(font);
        }
        if (texture != nullptr) {
            SDL_DestroyTexture(texture);
        }
        throw;
    }
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    SDL_DestroyTexture(texture);
    return res;
}

void WindowSDL::draw_(piece::SharedConstBoard board) {
}

void WindowSDL::draw_(const piece::Piece& piece, const piece::PiecePosition& piece_position) {
}

void WindowSDL::draw_next_(const piece::Piece& next_piece) {
}

void WindowSDL::draw_(const state::ScoreBoard& score_board) {
}

void WindowSDL::draw_(const state::EliminationList& elimination_list) {
}
}
