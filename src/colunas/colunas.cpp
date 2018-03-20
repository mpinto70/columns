#include "colunas.h"

#include "grafico/DesenhaTabuleiro.h"
#include "jogo/BoardController.h"
#include "jogo/GameController.h"
#include "jogo/StateObserver.h"
#include "piece/Board.h"
#include "util/Wait.h"

#include <atomic>
#include <iostream>
#include <thread>
#include <unistd.h>

namespace {
const std::string VERSAO = "0.5";

/// cores poss�veis
const std::vector<gui::Color> POSSIVEIS = { gui::GREEN, gui::RED, gui::BLUE, gui::YELLOW, gui::LAVENDER };

constexpr size_t TAMANHO_QUADRADINHO = 30;                           ///< tamanho de cada quadradinho em pixels
constexpr size_t STEPS_QUADRADINHO = 2;                              ///< passos em pixels dentro de cada quadradinho
constexpr size_t LARGURA = 8;                                        ///< largura do tabuleiro em quadradinhos
constexpr size_t ALTURA = 16;                                        ///< altura do tabuleiro em quadradinhos
constexpr size_t LARGURA_TELA = LARGURA * TAMANHO_QUADRADINHO + 200; ///< largura da tela
constexpr size_t ALTURA_TELA = ALTURA * TAMANHO_QUADRADINHO + 50;    ///< altura da tela

std::atomic<bool> inicializado; ///< marcador de inicializa��o
std::atomic<bool> quit;         ///< marcador de fim

/** espera pela condi��o se tornar \b true
 * @param condicao a condi��o de guarda
 */
static void esperaPor(std::atomic<bool>& condicao) {
    while (not condicao) {
        usleep(200);
    }
}

/** Observador da situa��o do jogo. */
class ColunasObs : public jogo::StateObserver {
public:
    /**
     * @param janela        a janela onde ser�o desenhadas os elementos
     * @param fonteNome     a fonte do nome da aplica��o
     * @param fontePlacar   a fonte do placar
     * @param desenhador    o desenhador de tabuleiro
     */
    ColunasObs(const grafico::SharedJanela& janela,
          const gui::Font& fonteNome,
          const gui::Font& fontePlacar,
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
    /** Atualiza os gr�ficos da situa��o do jogo.
     * @param situacao a situa��o atual do jogo
     */
    void update(const jogo::State& situacao) const override {
        janela_->limpa();
        janela_->escreve("Colunas!",
              gui::Point{ 10, ALTURA * TAMANHO_QUADRADINHO + 45 },
              fonteNome_,
              gui::BLUE);
        janela_->escreve("Placar",
              gui::Point{ 10 + LARGURA * TAMANHO_QUADRADINHO + 10, 50 },
              fonteNome_,
              gui::YELLOW);
        janela_->escreve(std::to_string(situacao.score_board().score().total()),
              gui::Point{ 10 + LARGURA * TAMANHO_QUADRADINHO + 10, 90 },
              fontePlacar_,
              gui::YELLOW);
        desenha_.desenha(*janela_, situacao, gui::WHITE);
        janela_->atualiza();
    }

private:
    grafico::SharedJanela janela_;      ///< a janela onde ser� mostrado o jogo
    gui::Font fonteNome_;               ///< a fonte do nome do sistema
    gui::Font fontePlacar_;             ///< a fonte do placar
    grafico::DesenhaTabuleiro desenha_; ///< o desenhador do conte�do do tabuleiro
};

/** Inicializa a interface gr�fica e executa o jogo.
 * @param mensagens o gerenciador de mensagens
 */
void executa(jogo::MensagemPtr mensagens) {
    inicializado = false;
    quit = false;
    try {
        auto janela = colunas::cria_janela(VERSAO, LARGURA_TELA, ALTURA_TELA);
        const grafico::DesenhaTabuleiro des(10, 15, TAMANHO_QUADRADINHO, STEPS_QUADRADINHO);
        const gui::Font fntNome("/usr/share/fonts/truetype/liberation/LiberationSerif-Regular.ttf", 25);
        const gui::Font fntPlacar("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf", 25);

        jogo::GameController cont(piece::Board(LARGURA, ALTURA, gui::BLACK),
              TAMANHO_QUADRADINHO / 2,
              score::Score(0),
              POSSIVEIS,
              jogo::StateObserverPtr(new ColunasObs(janela, fntNome, fntPlacar, des)),
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

void loop_input(jogo::MensagemPtr& mensagens) {
    util::Wait tempoInput(3);
    while (!quit) {
        tempoInput.reset();
        if (colunas::processa_input(mensagens) == colunas::InputResult::QUIT) {
            quit = true;
            break;
        }
        tempoInput.wait();
        // colocar o c�digo adicional aqui
    }
}

int run() {
    try {
        colunas::init_grafico();

        auto mensagens = std::make_shared<jogo::Message>();
        std::thread executeThread(executa, mensagens);

        esperaPor(inicializado);

        // quando sair do loop de input � porque deu quit
        loop_input(mensagens);

        mensagens->add(jogo::EMessage::Stop);
        executeThread.join();
        return 0;
    } catch (std::exception& e) {
        std::cout << "Erro: %s\n"
                  << e.what() << std::endl;
    }
    colunas::finaliza_grafico();

    std::cout << "FIM\n";
    return 0;
}
}

int main() {
    return run();
}
