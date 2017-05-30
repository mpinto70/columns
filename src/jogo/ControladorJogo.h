#pragma once

#include "jogo/ControladorTabuleiro.h"
#include "jogo/Mensagem.h"
#include "jogo/SituacaoObserver.h"
#include "gui/Cor.h"
#include "pontuacao/Placar.h"

#include <mutex>
#include <atomic>

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
        ControladorJogo(const peca::Tabuleiro & tabuleiro,
                        uint16_t maxSubLinha,
                        const pontuacao::Pontuacao & recorde,
                        const std::vector<gui::Cor> & possiveis,
                        SituacaoObserverPtr && obs,
                        MensagemPtr & msg);
        ControladorJogo(const ControladorJogo&) = delete;
        ControladorJogo& operator=(const ControladorJogo&) = delete;
        /** loop de execu��o. */
        void execute();
    private:
        ControladorTabuleiro tabuleiro_;            ///< o tabuleiro
        pontuacao::Placar placar_;                  ///< o placar
        peca::Peca proximaPeca_;                    ///< a pr�ximaa peca a cair no tabuleiro
        std::vector<gui::Cor> possiveis_;           ///< as cores poss�veis
        SituacaoObserverPtr observer_;              ///< observadores do jogo
        MensagemPtr mensagens_;                     ///< as mensagens
        std::atomic<bool> parar_;                   ///< marca de interrup��o de execu��o
        /** @return a situa��o atual do jogo.
         * @param lista a lista de quadradinhos a eliminar
         */
        Situacao montaSituacao(const jogo::ListaEliminacao & lista = jogo::ListaEliminacao()) const;
        /** processa as mensagens.
         * @param msgs as mensagens a processar
         */
        void processa(const Mensagem::Lista & msgs);
};

}
