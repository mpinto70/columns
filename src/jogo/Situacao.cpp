
#include "Situacao.h"

#include <utility>

namespace jogo {

Situacao::Situacao(const peca::Board& tabuleiro,
      const pontuacao::Placar& placar)
      : tabuleiro_(tabuleiro),
        placar_(placar),
        peca_(nullptr),
        posicaoPeca_(nullptr),
        eliminacao_(),
        proxima_(nullptr) {
}

Situacao::Situacao(const peca::Board& tabuleiro,
      const pontuacao::Placar& placar,
      const peca::Piece& caindo,
      const peca::PosicaoPeca& posicao,
      const peca::Piece& proxima)
      : tabuleiro_(tabuleiro),
        placar_(placar),
        peca_(new peca::Piece(caindo)),
        posicaoPeca_(new peca::PosicaoPeca(posicao)),
        eliminacao_(),
        proxima_(new peca::Piece(proxima)) {
}

Situacao::Situacao(const peca::Board& tabuleiro,
      const pontuacao::Placar& placar,
      const ListaEliminacao& lista,
      const peca::Piece& proxima)
      : tabuleiro_(tabuleiro),
        placar_(placar),
        peca_(nullptr),
        posicaoPeca_(nullptr),
        eliminacao_(lista),
        proxima_(new peca::Piece(proxima)) {
}

const peca::PosicaoPeca& Situacao::posicaoPeca() const {
    if (not temPeca()) {
        throw std::logic_error("Situacao::posicaoPeca - não há peça caindo no tabuleiro");
    }
    return *posicaoPeca_;
}

const peca::Piece& Situacao::peca() const {
    if (not temPeca()) {
        throw std::logic_error("Situacao::peca - não há peça caindo no tabuleiro");
    }
    return *peca_;
}

const peca::Piece& Situacao::proxima() const {
    if (not temProxima()) {
        throw std::logic_error("Situacao::proxima - não há próxima peça");
    }
    return *proxima_;
}

bool operator==(const Situacao& lhs, const Situacao& rhs) {
    using namespace std::rel_ops;
    if (lhs.tabuleiro() != rhs.tabuleiro()) {
        return false;
    }
    if (lhs.placar() != rhs.placar()) {
        return false;
    }
    if (lhs.temPeca() != rhs.temPeca()) {
        return false;
    }
    if (lhs.temPeca()) {
        if (lhs.peca() != rhs.peca()) {
            return false;
        }
        if (lhs.posicaoPeca() != rhs.posicaoPeca()) {
            return false;
        }
    }
    if (lhs.temProxima() != rhs.temProxima()) {
        return false;
    }
    if (lhs.temProxima()) {
        if (lhs.proxima() != rhs.proxima()) {
            return false;
        }
    }
    if (lhs.eliminacao() != rhs.eliminacao()) {
        return false;
    }

    return true;
}

bool operator!=(const Situacao& lhs, const Situacao& rhs) {
    return not(lhs == rhs);
}
}
