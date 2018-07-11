#include "WindowSDL.h"

#include <SDL2/SDL_ttf.h>

#include <stdexcept>

namespace graphics {

WindowSDL::WindowSDL(const std::string& name,
      size_t left,
      size_t top,
      size_t width,
      size_t height,
      const ColorTripletT& color)
      : width_(width),
        height_(height),
        window_(nullptr),
        renderer_(nullptr),
        color_{ color[0], color[1], color[2] } {
    window_ = SDL_CreateWindow(name.c_str(), left, top, width, height, SDL_WINDOW_SHOWN);
    if (window_ == nullptr) {
        throw std::runtime_error("WindowSDL - error creating window: " + std::string(SDL_GetError()));
    }
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer_ == nullptr) {
        throw std::runtime_error("WindowSDL - error creating renderer: " + std::string(SDL_GetError()));
    }
}

void WindowSDL::clear() {
    if (SDL_SetRenderDrawColor(renderer_, color_[0], color_[1], color_[2], SDL_ALPHA_OPAQUE) != 0) {
        throw std::runtime_error("WindowSDL::clear - SDL_SetRenderDrawColor error");
    }
    if (SDL_RenderClear(renderer_) != 0) {
        throw std::runtime_error("WindowSDL::clear - SDL_RenderClear error");
    }
}

void WindowSDL::update() {
    SDL_RenderPresent(renderer_);
}

void WindowSDL::line(int x1,
      int y1,
      int x2,
      int y2,
      const ColorTripletT& sdl_color) {
    if (SDL_SetRenderDrawColor(renderer_, sdl_color[0], sdl_color[1], sdl_color[2], SDL_ALPHA_OPAQUE) != 0) {
        throw std::runtime_error("WindowSDL::line - error no SDL_SetRenderDrawColor");
    }

    if (SDL_RenderDrawLine(renderer_, x1, y1, x2, y2) != 0) {
        throw std::runtime_error("WindowSDL::line - error no SDL_RenderDrawLine");
    }
}

void WindowSDL::rectangle(const SDL_Rect& rect, const ColorTripletT& color) {
    if (SDL_SetRenderDrawColor(renderer_, color[0], color[1], color[2], SDL_ALPHA_OPAQUE) != 0) {
        throw std::runtime_error("WindowSDL::rectangle - error no SDL_SetRenderDrawColor");
    }
    if (SDL_RenderDrawRect(renderer_, &rect)) {
        throw std::runtime_error("WindowSDL::rectangle - error no SDL_RenderDrawRect");
    }
}

void WindowSDL::fill(const SDL_Rect& rect, const ColorTripletT& color) {
    if (SDL_SetRenderDrawColor(renderer_, color[0], color[1], color[2], SDL_ALPHA_OPAQUE) != 0) {
        throw std::runtime_error("WindowSDL::fill - error no SDL_SetRenderDrawColor");
    }
    if (SDL_RenderFillRect(renderer_, &rect) != 0) {
        throw std::runtime_error("WindowSDL::fill - error no SDL_RenderFillRect");
    }
}

SDL_Rect WindowSDL::write(const std::string& text,
      int x,
      int y,
      const std::string& font_name,
      int font_size,
      const ColorTripletT& color) {
    TTF_Font* font = nullptr;
    SDL_Surface* surface = nullptr;
    SDL_Texture* texture = nullptr;
    try {
        const SDL_Color sdl_color = { color[0], color[1], color[2] };

        font = TTF_OpenFont(font_name.c_str(), font_size);
        if (font == nullptr) {
            throw std::runtime_error("WindowSDL::write - opening font " + font_name);
        }

        //We need to first render to a surface as that's what TTF_RenderText
        //returns, then load that surface into a texture
        surface = TTF_RenderText_Blended(font, text.c_str(), sdl_color);
        if (surface == nullptr) {
            throw std::runtime_error("WindowSDL::write - getting the surface " + text);
        }

        texture = SDL_CreateTextureFromSurface(renderer_, surface);
        if (texture == nullptr) {
            throw std::runtime_error("WindowSDL::write - getting the texture");
        }

        //Get the texture w/h so we can center it in the screen
        SDL_Rect dst = { x, y, 0, 0 };
        //Query the texture to get its width and height to use
        if (SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h) != 0) {
            throw std::runtime_error("WindowSDL::write - SDL_QueryTexture error");
        }

        if (SDL_RenderCopy(renderer_, texture, nullptr, &dst) != 0) {
            throw std::runtime_error("WindowSDL::write - SDL_RenderCopy error");
        }
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        SDL_DestroyTexture(texture);
        return dst;
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
}
}
