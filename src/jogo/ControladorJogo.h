#pragma once

#include "gui/Color.h"
#include "jogo/BoardController.h"
#include "jogo/Message.h"
#include "jogo/StateObserver.h"
#include "score/ScoreBoard.h"

#include <atomic>
#include <mutex>

namespace jogo {
/** Respons�vel controlar o jogo:
 * \li controle do tabuleiro;
 * \li controle do placar.
 */
class ControladorJogo {
public:
    /**
     * @param tabuleiro o tabuleiro em que o controlador vai gerenciar a queda da pe�a
     * @param maxSubLinha o m�ximo de subdivis�o do passo da pe�a
     * @param recorde o recorde
     * @param possiveis as cores poss�veis
     * @param obs o observer da situa��o do jogo
     * @param msg o gerenciador de mensagens
     */
    ControladorJogo(const piece::Board& tabuleiro,
          uint16_t maxSubLinha,
          const score::Score& recorde,
          const std::vector<gui::Color>& possiveis,
          StateObserverPtr&& obs,
          MensagemPtr& msg);
    ControladorJogo(const ControladorJogo&) = delete;
    ControladorJogo& operator=(const ControladorJogo&) = delete;
    /** loop de execu��o. */
    void execute();

private:
    BoardController tabuleiro_;         ///< o tabuleiro
    score::ScoreBoard placar_;          ///< o placar
    piece::Piece proximaPeca_;          ///< a pr�ximaa piece a cair no tabuleiro
    std::vector<gui::Color> possiveis_; ///< as cores poss�veis
    StateObserverPtr observer_;         ///< observadores do jogo
    MensagemPtr mensagens_;             ///< as mensagens
    std::atomic<bool> parar_;           ///< marca de interrup��o de execu��o
    /** @return a situa��o atual do jogo.
     * @param lista a lista de quadradinhos a eliminar
     */
    State montaSituacao(const jogo::EliminationList& lista = jogo::EliminationList()) const;
    /** processa as mensagens.
     * @param msgs as mensagens a processar
     */
    void processa(const Message::Lista& msgs);
};
}
