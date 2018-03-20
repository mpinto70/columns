#include "colunas/colunas.h"

#include "grafico/SDL/JanelaSDL.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace colunas {
/** retorna a mensagem de erro da SDL
 * @param msg o preâmbulo da mensagem de erro
 */
static std::string montaLogSDL(const std::string& msg) {
    return msg + " error: " + SDL_GetError();
}

grafico::SharedJanela cria_janela(const std::string& versao,
      size_t largura_tela,
      size_t altura_tela) {
    return std::make_shared<grafico::JanelaSDL>("Colunas " + versao, 1000, 100, largura_tela, altura_tela, gui::GRAY);
}

InputResult processa_input(game::MensagemPtr& mensagens) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        //If user closes the window
        if (e.type == SDL_QUIT) {
            return InputResult::QUIT;
        }
        //If user presses any key
        if (e.type == SDL_KEYDOWN) {
            /* Check the SDLKey values and move change the coords */
            switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                    mensagens->add(game::EMessage::MoveLeft);
                    break;
                case SDLK_RIGHT:
                    mensagens->add(game::EMessage::MoveRight);
                    break;
                case SDLK_UP:
                    mensagens->add(game::EMessage::RollUp);
                    break;
                case SDLK_DOWN:
                    mensagens->add(game::EMessage::RollDown);
                    break;
                case SDLK_SPACE:
                    mensagens->add(game::EMessage::MoveDown);
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

void init_grafico() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        throw std::runtime_error(montaLogSDL("SDL_Init"));
    }

    if (TTF_Init() != 0) {
        throw std::runtime_error(montaLogSDL("TTF_Init"));
    }
}

void finaliza_grafico() {
    SDL_Quit();
}
}
