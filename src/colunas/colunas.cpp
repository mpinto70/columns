#include "grafico/DesenhaTabuleiro.h"
#include "grafico/SDL/JanelaSDL.h"
#include "jogo/SituacaoObserver.h"
#include "jogo/ControladorTabuleiro.h"
#include "jogo/ControladorJogo.h"
#include "peca/Tabuleiro.h"
#include "util/Espera.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <unistd.h>
#include <atomic>
#include <thread>

namespace colunas {
const std::string VERSAO = "0.5";

/// cores possíveis
const std::vector<gui::Cor> POSSIVEIS = { gui::Verde, gui::Vermelho, gui::Azul, gui::Amarelo, gui::Lavanda };

constexpr size_t TAMANHO_QUADRADINHO = 30;                              ///< tamanho de cada quadradinho em pixels
constexpr size_t STEPS_QUADRADINHO = 2;                                 ///< passos em pixels dentro de cada quadradinho
constexpr size_t LARGURA = 8;                                           ///< largura do tabuleiro em quadradinhos
constexpr size_t ALTURA = 16;                                           ///< altura do tabuleiro em quadradinhos
constexpr size_t LARGURA_TELA = LARGURA * TAMANHO_QUADRADINHO + 200;    ///< largura da tela
constexpr size_t ALTURA_TELA = ALTURA * TAMANHO_QUADRADINHO + 50;       ///< altura da tela

std::atomic<bool> inicializado; ///< marcador de inicialização
std::atomic<bool> quit;         ///< marcador de fim

/** retorna a mensagem de erro da SDL
 * @param msg o preâmbulo da mensagem de erro
 */
static std::string montaLogSDL(const std::string& msg) {
    return msg + " error: " + SDL_GetError();
}

/** espera pela condição se tornar \b true
 * @param condicao a condição de guarda
 */
static void esperaPor(std::atomic<bool>& condicao) {
    while (not condicao) {
        usleep(200);
    }
}

/** Observador da situação do jogo. */
class ColunasObs: public jogo::SituacaoObserver {
public:
    /**
     * @param janela        a janela onde serão desenhadas os elementos
     * @param fonteNome     a fonte do nome da aplicação
     * @param fontePlacar   a fonte do placar
     * @param desenhador    o desenhador de tabuleiro
     */
    ColunasObs(const grafico::SharedJanela& janela,
               const gui::Fonte& fonteNome,
               const gui::Fonte& fontePlacar,
               const grafico::DesenhaTabuleiro& desenhador)
        : janela_(janela),
          fonteNome_(fonteNome),
          fontePlacar_(fontePlacar),
          desenha_(desenhador) {
        if (janela_.get() == nullptr) {
            throw std::invalid_argument("ColunasObs - janela nula");
        }
    }
    ~ColunasObs() override = default;
    /** Atualiza os gráficos da situação do jogo.
     * @param situacao a situação atual do jogo
     */
    void atualiza(const jogo::Situacao& situacao) const override {
        janela_->limpa();
        janela_->escreve("Colunas!",
                         gui::Ponto {10, ALTURA * TAMANHO_QUADRADINHO + 45},
                         fonteNome_,
                         gui::Azul);
        janela_->escreve("Placar",
                         gui::Ponto {10 + LARGURA * TAMANHO_QUADRADINHO + 10, 50},
                         fonteNome_,
                         gui::Amarelo);
        janela_->escreve(std::to_string(situacao.placar().pontuacao().total()),
                         gui::Ponto {10 + LARGURA * TAMANHO_QUADRADINHO + 10, 90},
                         fontePlacar_,
                         gui::Amarelo);
        desenha_.desenha(*janela_, situacao, gui::Branco);
        janela_->atualiza();
    }
private:
    grafico::SharedJanela janela_;      ///< a janela onde será mostrado o jogo
    gui::Fonte fonteNome_;              ///< a fonte do nome do sistema
    gui::Fonte fontePlacar_;            ///< a fonte do placar
    grafico::DesenhaTabuleiro desenha_; ///< o desenhador do conteúdo do tabuleiro
};

/** Inicializa a interface gráfica e executa o jogo.
 * @param mensagens o gerenciador de mensagens
 */
void executa(jogo::MensagemPtr mensagens) {
    inicializado = false;
    quit = false;
    try {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
            throw std::runtime_error(montaLogSDL("SDL_Init"));
        }

        if (TTF_Init() != 0) {
            throw std::runtime_error(montaLogSDL("TTF_Init"));
        }

        grafico::SharedJanela janela(new grafico::JanelaSDL("Colunas " + VERSAO, 1000, 100, LARGURA_TELA, ALTURA_TELA, gui::Cinza));
        const grafico::DesenhaTabuleiro des(10, 15, TAMANHO_QUADRADINHO, STEPS_QUADRADINHO);
        const gui::Fonte fntNome("/usr/share/fonts/truetype/liberation/LiberationSerif-Regular.ttf", 25);
        const gui::Fonte fntPlacar("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf", 25);

        jogo::ControladorJogo cont(peca::Tabuleiro(LARGURA, ALTURA, gui::Preto),
                                   TAMANHO_QUADRADINHO / 2,
                                   pontuacao::Pontuacao(0),
                                   POSSIVEIS,
                                   jogo::SituacaoObserverPtr(new ColunasObs(janela, fntNome, fntPlacar, des)),
                                   mensagens);

        inicializado = true;

        cont.execute();
        quit = true;
    } catch (std::exception& e) {
        std::cout << "Erro: " << e.what() << std::endl;
        quit = true;
        inicializado = true;
    }
}

enum class InputResult {
    QUIT,
    CONTINUE,
};

InputResult processa_input(jogo::MensagemPtr& mensagens) {
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
                mensagens->registra(jogo::EMensagem::moveEsquerda);
                break;
            case SDLK_RIGHT:
                mensagens->registra(jogo::EMensagem::moveDireita);
                break;
            case SDLK_UP:
                mensagens->registra(jogo::EMensagem::rolaCima);
                break;
            case SDLK_DOWN:
                mensagens->registra(jogo::EMensagem::rolaBaixo);
                break;
            case SDLK_SPACE:
                mensagens->registra(jogo::EMensagem::moveBaixo);
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

void loop_input(jogo::MensagemPtr& mensagens) {
    util::Espera tempoInput(3);
    while (!quit) {
        tempoInput.zera();
        if (processa_input(mensagens) == InputResult::QUIT) {
            quit = true;
        }
        tempoInput.espera();
        // colocar o código adicional aqui
    }
}

int run() {
    try {
        auto mensagens = std::make_shared<jogo::Mensagem>();
        std::thread executeThread(executa, mensagens);

        esperaPor(inicializado);

        // quando sair do loop de input é porque deu quit
        loop_input(mensagens);

        mensagens->registra(jogo::EMensagem::parar);
        executeThread.join();
        return 0;
    } catch (std::exception& e) {
        std::cout << "Erro: %s\n" << e.what() << std::endl;
    }
    SDL_Quit();

    std::cout << "FIM\n";
    return 0;
}

}

int main() {
    return colunas::run();
}
