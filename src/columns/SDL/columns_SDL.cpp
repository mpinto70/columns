#include "columns/columns.h"
#include "graphics/SDL/WindowSDL.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace columns {
static std::string create_log_SDL(const std::string& preamble) {
    return preamble + " error: " + SDL_GetError();
}

graphics::WindowPtr create_window(const std::string& version,
      size_t screen_width,
      size_t screen_height) {
    return std::make_unique<graphics::WindowSDL>("Columns " + version,
          1000,
          100,
          screen_width,
          screen_height,
          gui::Color::GRAY);
}

InputResult process_input(game::SharedMessage& messages) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        //If user closes the window
        if (event.type == SDL_QUIT) {
            return InputResult::QUIT;
        }
        //If user presses any key
        if (event.type == SDL_KEYDOWN) {
            /* Check the SDLKey values and move change the coords */
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    messages->add(game::EMessage::MoveLeft);
                    break;
                case SDLK_RIGHT:
                    messages->add(game::EMessage::MoveRight);
                    break;
                case SDLK_UP:
                    messages->add(game::EMessage::RollUp);
                    break;
                case SDLK_DOWN:
                    messages->add(game::EMessage::RollDown);
                    break;
                case SDLK_SPACE:
                    messages->add(game::EMessage::DropDown);
                    break;
                case SDLK_ESCAPE:
                    return InputResult::QUIT;
                default:
                    break;
            }
        }
    }
    return InputResult::CONTINUE;
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
}
