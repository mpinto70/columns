#include "ControladorJogo.h"

#include "util/Wait.h"

#include <stdexcept>
#include <unistd.h>

namespace jogo {

ControladorJogo::ControladorJogo(const piece::Board& tabuleiro,
      const uint16_t maxSubLinha,
      const score::Score& recorde,
      const std::vector<gui::Color>& possiveis,
      StateObserverPtr&& obs,
      MensagemPtr& msg)
      : tabuleiro_(tabuleiro, maxSubLinha),
        placar_(recorde),
        proximaPeca_(piece::Piece::create(possiveis)),
        possiveis_(possiveis),
        observer_(std::move(obs)),
        mensagens_(msg),
        parar_(false) {
    if (observer_.get() == nullptr) {
        throw std::invalid_argument("ControladorJogo - observer nulo");
    }
    if (possiveis_.empty()) {
        throw std::invalid_argument("ControladorJogo - sem cores possíveis");
    }
    if (mensagens_.get() == nullptr) {
        throw std::invalid_argument("ControladorJogo - mensagem nula");
    }
}

void ControladorJogo::execute() {
    parar_ = false;
    util::Wait tempoPasso(10);

    while (not parar_) {
        tempoPasso.reset();
        if (tabuleiro_.temPeca()) {
            tabuleiro_.passo();
        } else {
            EliminationList listaEliminacao;
            while (not(listaEliminacao = tabuleiro_.determinaEliminacao()).empty()) {
                util::Wait tempoElimina(300);
                observer_->update(montaSituacao(listaEliminacao));
                placar_.add(listaEliminacao.size());
                tabuleiro_.elimina(listaEliminacao);
                //printf("\n%s (%d) - %d\n", __FILE__, __LINE__, placar_.score().total());
                tempoElimina.wait();
                mensagens_->limpa();
            }
            tempoPasso.reset();
            if (not tabuleiro_.adicionaPeca(proximaPeca_)) {
                return;
            }
            proximaPeca_ = piece::Piece::create(possiveis_);
        }
        processa(mensagens_->recupera());
        observer_->update(montaSituacao());
        tempoPasso.wait();
    }
}

State ControladorJogo::montaSituacao(const jogo::EliminationList& lista) const {
    if (tabuleiro_.temPeca()) {
        return State(tabuleiro_.tabuleiro(),
              placar_,
              tabuleiro_.piece(),
              tabuleiro_.posicaoPeca(),
              proximaPeca_);
    } else {
        return State(tabuleiro_.tabuleiro(),
              placar_,
              lista,
              proximaPeca_);
    }
}

void ControladorJogo::processa(const Mensagem::Lista& msgs) {
    for (const auto msg : msgs) {
        switch (msg) {
            case EMensagem::moveEsquerda:
                tabuleiro_.moveEsquerda();
                break;
            case EMensagem::moveDireita:
                tabuleiro_.moveDireita();
                break;
            case EMensagem::moveBaixo:
                while (tabuleiro_.temPeca()) {
                    //printf("\n%s (%d) - PASSO(%d)\n", __FILE__, __LINE__, ++cont);
                    tabuleiro_.passo();
                    tabuleiro_.passo();
                    tabuleiro_.passo();
                    tabuleiro_.passo();
                    tabuleiro_.passo();
                    tabuleiro_.passo();
                    observer_->update(montaSituacao());
                }
                break;
            case EMensagem::rolaBaixo:
                tabuleiro_.rolaParaBaixo();
                break;
            case EMensagem::rolaCima:
                tabuleiro_.rolaParaCima();
                break;
            case EMensagem::parar:
                parar_ = true;
                break;
        }
        observer_->update(montaSituacao());
    }
}
}
