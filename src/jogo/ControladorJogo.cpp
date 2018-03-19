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
        if (tabuleiro_.has_piece()) {
            tabuleiro_.step();
        } else {
            EliminationList listaEliminacao;
            while (not(listaEliminacao = tabuleiro_.determine_elimination()).empty()) {
                util::Wait tempoElimina(300);
                observer_->update(montaSituacao(listaEliminacao));
                placar_.add(listaEliminacao.size());
                tabuleiro_.eliminate(listaEliminacao);
                //printf("\n%s (%d) - %d\n", __FILE__, __LINE__, placar_.score().total());
                tempoElimina.wait();
                mensagens_->clear();
            }
            tempoPasso.reset();
            if (not tabuleiro_.add_piece(proximaPeca_)) {
                return;
            }
            proximaPeca_ = piece::Piece::create(possiveis_);
        }
        processa(mensagens_->get());
        observer_->update(montaSituacao());
        tempoPasso.wait();
    }
}

State ControladorJogo::montaSituacao(const jogo::EliminationList& lista) const {
    if (tabuleiro_.has_piece()) {
        return State(tabuleiro_.board(),
              placar_,
              tabuleiro_.piece(),
              tabuleiro_.piece_position(),
              proximaPeca_);
    } else {
        return State(tabuleiro_.board(),
              placar_,
              lista,
              proximaPeca_);
    }
}

void ControladorJogo::processa(const Message::Lista& msgs) {
    for (const auto msg : msgs) {
        switch (msg) {
            case EMessage::MoveLeft:
                tabuleiro_.move_left();
                break;
            case EMessage::MoveRight:
                tabuleiro_.move_right();
                break;
            case EMessage::MoveDown:
                while (tabuleiro_.has_piece()) {
                    //printf("\n%s (%d) - PASSO(%d)\n", __FILE__, __LINE__, ++cont);
                    tabuleiro_.step();
                    tabuleiro_.step();
                    tabuleiro_.step();
                    tabuleiro_.step();
                    tabuleiro_.step();
                    tabuleiro_.step();
                    observer_->update(montaSituacao());
                }
                break;
            case EMessage::RollDown:
                tabuleiro_.roll_down();
                break;
            case EMessage::RollUp:
                tabuleiro_.roll_up();
                break;
            case EMessage::Stop:
                parar_ = true;
                break;
        }
        observer_->update(montaSituacao());
    }
}
}
