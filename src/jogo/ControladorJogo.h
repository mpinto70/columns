#pragma once

#include "gui/Color.h"
#include "jogo/ControladorTabuleiro.h"
#include "jogo/Mensagem.h"
#include "jogo/SituacaoObserver.h"
#include "pontuacao/Placar.h"

#include <atomic>
#include <mutex>

namespace jogo {
/** Responsável controlar o jogo:
 * \li controle do tabuleiro;
 * \li controle do placar.
 */
class ControladorJogo {
public:
    /**
     * @param tabuleiro o tabuleiro em que o controlador vai gerenciar a queda da peça
     * @param maxSubLinha o máximo de subdivisão do passo da peça
     * @param recorde o recorde
     * @param possiveis as cores possíveis
     * @param obs o observer da situação do jogo
     * @param msg o gerenciador de mensagens
     */
    ControladorJogo(const piece::Board& tabuleiro,
          uint16_t maxSubLinha,
          const pontuacao::Score& recorde,
          const std::vector<gui::Color>& possiveis,
          SituacaoObserverPtr&& obs,
          MensagemPtr& msg);
    ControladorJogo(const ControladorJogo&) = delete;
    ControladorJogo& operator=(const ControladorJogo&) = delete;
    /** loop de execução. */
    void execute();

private:
    ControladorTabuleiro tabuleiro_;    ///< o tabuleiro
    pontuacao::Placar placar_;          ///< o placar
    piece::Piece proximaPeca_;           ///< a próximaa piece a cair no tabuleiro
    std::vector<gui::Color> possiveis_; ///< as cores possíveis
    SituacaoObserverPtr observer_;      ///< observadores do jogo
    MensagemPtr mensagens_;             ///< as mensagens
    std::atomic<bool> parar_;           ///< marca de interrupção de execução
    /** @return a situação atual do jogo.
     * @param lista a lista de quadradinhos a eliminar
     */
    Situacao montaSituacao(const jogo::ListaEliminacao& lista = jogo::ListaEliminacao()) const;
    /** processa as mensagens.
     * @param msgs as mensagens a processar
     */
    void processa(const Mensagem::Lista& msgs);
};
}
