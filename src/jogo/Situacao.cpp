
#include "Situacao.h"

#include <utility>

namespace jogo {

Situacao::Situacao(const piece::Board& tabuleiro,
      const pontuacao::Placar& placar)
      : tabuleiro_(tabuleiro),
        placar_(placar),
        peca_(nullptr),
        posicaoPeca_(nullptr),
        eliminacao_(),
        proxima_(nullptr) {
}

Situacao::Situacao(const piece::Board& tabuleiro,
      const pontuacao::Placar& placar,
      const piece::Piece& caindo,
      const piece::PiecePosition& posicao,
      const piece::Piece& proxima)
      : tabuleiro_(tabuleiro),
        placar_(placar),
        peca_(new piece::Piece(caindo)),
        posicaoPeca_(new piece::PiecePosition(posicao)),
        eliminacao_(),
        proxima_(new piece::Piece(proxima)) {
}

Situacao::Situacao(const piece::Board& tabuleiro,
      const pontuacao::Placar& placar,
      const ListaEliminacao& lista,
      const piece::Piece& proxima)
      : tabuleiro_(tabuleiro),
        placar_(placar),
        peca_(nullptr),
        posicaoPeca_(nullptr),
        eliminacao_(lista),
        proxima_(new piece::Piece(proxima)) {
}

const piece::PiecePosition& Situacao::posicaoPeca() const {
    if (not temPeca()) {
        throw std::logic_error("Situacao::posicaoPeca - não há peça caindo no tabuleiro");
    }
    return *posicaoPeca_;
}

const piece::Piece& Situacao::piece() const {
    if (not temPeca()) {
        throw std::logic_error("Situacao::piece - não há peça caindo no tabuleiro");
    }
    return *peca_;
}

const piece::Piece& Situacao::proxima() const {
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
        if (lhs.piece() != rhs.piece()) {
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
