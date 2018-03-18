#include "JanelaSDL.h"

#include <SDL2/SDL_ttf.h>

#include <stdexcept>

namespace grafico {
JanelaSDL::JanelaSDL(const std::string& nome,
      const uint16_t left,
      const uint16_t top,
      const uint16_t width,
      const uint16_t height,
      const gui::Color& cor)
      : Janela(nome, width, height),
        window_(nullptr),
        renderer_(nullptr),
        cor_(cor) {
    window_ = SDL_CreateWindow(nome.c_str(), left, top, width, height, SDL_WINDOW_SHOWN);
    if (window_ == nullptr) {
        throw std::runtime_error("JanelaSDL - erro criando a janela: " + std::string(SDL_GetError()));
    }
    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer_ == nullptr) {
        throw std::runtime_error("JanelaSDL - erro criando o renderer: " + std::string(SDL_GetError()));
    }
}

JanelaSDL::~JanelaSDL() {
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
}

void JanelaSDL::limpa() {
    if (SDL_SetRenderDrawColor(renderer_, cor_.R, cor_.G, cor_.B, SDL_ALPHA_OPAQUE) != 0) {
        throw std::runtime_error("JanelaSDL::limpa - erro no SDL_SetRenderDrawColor");
    }
    if (SDL_RenderClear(renderer_) != 0) {
        throw std::runtime_error("JanelaSDL::limpa - erro no SDL_RenderClear");
    }
}

void JanelaSDL::atualiza() {
    SDL_RenderPresent(renderer_);
}

void JanelaSDL::linha_(const uint16_t x1,
      const uint16_t y1,
      const uint16_t x2,
      const uint16_t y2,
      const gui::Color& cor) {
    if (SDL_SetRenderDrawColor(renderer_, cor.R, cor.G, cor.B, SDL_ALPHA_OPAQUE) != 0) {
        throw std::runtime_error("JanelaSDL::linha_ - erro no SDL_SetRenderDrawColor");
    }

    if (SDL_RenderDrawLine(renderer_, x1, y1, x2, y2) != 0) {
        throw std::runtime_error("JanelaSDL::linha_ - erro no SDL_RenderDrawLine");
    }
}

void JanelaSDL::retangulo_(const uint16_t x1,
      const uint16_t y1,
      const uint16_t x2,
      const uint16_t y2,
      const gui::Color& cor) {
    const SDL_Rect rect = { x1, y1, x2 - x1 + 1, y2 - y1 + 1 };
    if (SDL_SetRenderDrawColor(renderer_, cor.R, cor.G, cor.B, SDL_ALPHA_OPAQUE) != 0) {
        throw std::runtime_error("JanelaSDL::retangulo_ - erro no SDL_SetRenderDrawColor");
    }
    if (SDL_RenderDrawRect(renderer_, &rect)) {
        throw std::runtime_error("JanelaSDL::retangulo_ - erro no SDL_RenderDrawRect");
    }
}

void JanelaSDL::preenche_(const uint16_t x1,
      const uint16_t y1,
      const uint16_t x2,
      const uint16_t y2,
      const gui::Color& cor) {
    const SDL_Rect rect = { x1, y1, x2 - x1 + 1, y2 - y1 + 1 };
    if (SDL_SetRenderDrawColor(renderer_, cor.R, cor.G, cor.B, SDL_ALPHA_OPAQUE) != 0) {
        throw std::runtime_error("JanelaSDL::preenche_ - erro no SDL_SetRenderDrawColor");
    }
    if (SDL_RenderFillRect(renderer_, &rect) != 0) {
        throw std::runtime_error("JanelaSDL::preenche_ - erro no SDL_RenderFillRect");
    }
}

gui::Rectangle JanelaSDL::escreve_(const std::string& texto,
      const uint16_t x,
      const uint16_t y,
      const gui::Font& fonte,
      const gui::Color& cor) {
    //We'll render the string "TTF fonts are cool!" in white
    //Color is in RGB format
    TTF_Font* font = nullptr;
    SDL_Surface* surf = nullptr;
    SDL_Texture* texture = nullptr;
    gui::Rectangle res(0, 0, 0, 0);
    try {
        const SDL_Color color = { cor.R, cor.G, cor.B };
        //Open the font
        font = TTF_OpenFont(fonte.name().c_str(), fonte.size());
        if (font == nullptr) {
            throw std::runtime_error("JanelaSDL::escreve_ - abertura da fonte " + fonte.name());
        }

        //We need to first render to a surface as that's what TTF_RenderText
        //returns, then load that surface into a texture
        surf = TTF_RenderText_Blended(font, texto.c_str(), color);
        if (surf == nullptr) {
            throw std::runtime_error("JanelaSDL::escreve_ - obtenção da superfície para o texto " + texto);
        }

        texture = SDL_CreateTextureFromSurface(renderer_, surf);
        if (texture == nullptr) {
            throw std::runtime_error("JanelaSDL::escreve_ - obtenção da textura");
        }

        //Get the texture w/h so we can center it in the screen
        SDL_Rect dst;
        dst.x = x;
        dst.y = y;
        //Query the texture to get its width and height to use
        if (SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h) != 0) {
            throw std::runtime_error("JanelaSDL::escreve_ - erro no SDL_QueryTexture");
        }

        res = gui::Rectangle(x, y, x + dst.w, y + dst.h);
        if (SDL_RenderCopy(renderer_, texture, NULL, &dst) != 0) {
            throw std::runtime_error("JanelaSDL::escreve_ - erro no SDL_RenderCopy");
        }
    } catch (...) {
        //Clean up the surface and font
        if (surf != nullptr) {
            SDL_FreeSurface(surf);
        }
        if (font != nullptr) {
            TTF_CloseFont(font);
        }
        if (texture != nullptr) {
            SDL_DestroyTexture(texture);
        }
        throw;
    }
    SDL_FreeSurface(surf);
    TTF_CloseFont(font);
    SDL_DestroyTexture(texture);
    return res;
}
}
