#include "WindowSDL.h"

#include <SDL2/SDL_ttf.h>

#include <stdexcept>

namespace grafico {
WindowSDL::WindowSDL(const std::string& name,
      const uint16_t left,
      const uint16_t top,
      const uint16_t width,
      const uint16_t height,
      const gui::Color& color)
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
    if (SDL_SetRenderDrawColor(renderer_, color_.R, color_.G, color_.B, SDL_ALPHA_OPAQUE) != 0) {
        throw std::runtime_error("WindowSDL::clear - SDL_SetRenderDrawColor error");
    }
    if (SDL_RenderClear(renderer_) != 0) {
        throw std::runtime_error("WindowSDL::clear - SDL_RenderClear error");
    }
}

void WindowSDL::update() {
    SDL_RenderPresent(renderer_);
}

void WindowSDL::line_(const uint16_t x1,
      const uint16_t y1,
      const uint16_t x2,
      const uint16_t y2,
      const gui::Color& color) {
    if (SDL_SetRenderDrawColor(renderer_, color.R, color.G, color.B, SDL_ALPHA_OPAQUE) != 0) {
        throw std::runtime_error("WindowSDL::linha_ - erro no SDL_SetRenderDrawColor");
    }

    if (SDL_RenderDrawLine(renderer_, x1, y1, x2, y2) != 0) {
        throw std::runtime_error("WindowSDL::linha_ - erro no SDL_RenderDrawLine");
    }
}

void WindowSDL::rectangle_(const uint16_t x1,
      const uint16_t y1,
      const uint16_t x2,
      const uint16_t y2,
      const gui::Color& color) {
    const SDL_Rect rect = { x1, y1, x2 - x1 + 1, y2 - y1 + 1 };
    if (SDL_SetRenderDrawColor(renderer_, color.R, color.G, color.B, SDL_ALPHA_OPAQUE) != 0) {
        throw std::runtime_error("WindowSDL::retangulo_ - erro no SDL_SetRenderDrawColor");
    }
    if (SDL_RenderDrawRect(renderer_, &rect)) {
        throw std::runtime_error("WindowSDL::retangulo_ - erro no SDL_RenderDrawRect");
    }
}

void WindowSDL::fill_(const uint16_t x1,
      const uint16_t y1,
      const uint16_t x2,
      const uint16_t y2,
      const gui::Color& color) {
    const SDL_Rect rect = { x1, y1, x2 - x1 + 1, y2 - y1 + 1 };
    if (SDL_SetRenderDrawColor(renderer_, color.R, color.G, color.B, SDL_ALPHA_OPAQUE) != 0) {
        throw std::runtime_error("WindowSDL::preenche_ - erro no SDL_SetRenderDrawColor");
    }
    if (SDL_RenderFillRect(renderer_, &rect) != 0) {
        throw std::runtime_error("WindowSDL::preenche_ - erro no SDL_RenderFillRect");
    }
}

gui::Rectangle WindowSDL::write_(const std::string& texto,
      const uint16_t x,
      const uint16_t y,
      const gui::Font& fonte,
      const gui::Color& color) {
    TTF_Font* font = nullptr;
    SDL_Surface* surface = nullptr;
    SDL_Texture* texture = nullptr;
    gui::Rectangle res(0, 0, 0, 0);
    try {
        const SDL_Color sdl_color = { color.R, color.G, color.B };
        font = TTF_OpenFont(fonte.name().c_str(), fonte.size());
        if (font == nullptr) {
            throw std::runtime_error("WindowSDL::write_ - opening font " + fonte.name());
        }

        //We need to first render to a surface as that's what TTF_RenderText
        //returns, then load that surface into a texture
        surface = TTF_RenderText_Blended(font, texto.c_str(), sdl_color);
        if (surface == nullptr) {
            throw std::runtime_error("WindowSDL::write_ - getting the surface " + texto);
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
        if (SDL_RenderCopy(renderer_, texture, NULL, &dst) != 0) {
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
}
