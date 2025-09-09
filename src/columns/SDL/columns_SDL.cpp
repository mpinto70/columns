#include "columns/columns.h"
#include "graphics/SDL/WindowSDL.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <stdexcept>

namespace columns {
static std::string create_log_SDL(const std::string& preamble) {
    return preamble + " error: " + SDL_GetError();
}

void init_graphics() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        throw std::runtime_error(create_log_SDL("SDL_Init"));
    }

    if (TTF_Init() != 0) {
        throw std::runtime_error(create_log_SDL("TTF_Init"));
    }
}

void stop_graphics() {
    SDL_Quit();
}
} // namespace columns
