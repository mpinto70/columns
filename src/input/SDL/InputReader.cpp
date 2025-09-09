#include "InputReader.h"

#include <SDL2/SDL.h>

namespace input {
namespace sdl {
game::Messages::List InputReader::read_input_() {
    game::Messages::List res;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // If user closes the window
        if (event.type == SDL_QUIT) {
            res.push_back(game::EMessage::Stop);
            return res;
        }
        // If user presses any key
        if (event.type == SDL_KEYDOWN) {
            /* Check the SDLKey values and move change the coordinates */
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    res.push_back(game::EMessage::MoveLeft);
                    break;
                case SDLK_RIGHT:
                    res.push_back(game::EMessage::MoveRight);
                    break;
                case SDLK_UP:
                    res.push_back(game::EMessage::RollUp);
                    break;
                case SDLK_DOWN:
                    res.push_back(game::EMessage::RollDown);
                    break;
                case SDLK_SPACE:
                    res.push_back(game::EMessage::DropDown);
                    break;
                case SDLK_ESCAPE:
                    res.push_back(game::EMessage::Stop);
                    return res;
                default:
                    break;
            }
        }
    }
    return res;
}
} // namespace sdl
} // namespace input
