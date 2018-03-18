#pragma once

#include "piece/Board.h"
#include "piece/Piece.h"
#include "piece/PiecePosition.h"
#include "score/ScoreBoard.h"
#include <memory>

namespace jogo {
/** tipo de item de casa a ser eliminada do tabuleiro. */
typedef std::pair<uint16_t, uint16_t> ItemEliminacao;
/** tipo da lista de casas a serem eliminadas do tabuleiro. */
typedef std::vector<ItemEliminacao> ListaEliminacao;
/** Respons�vel por registrar a situa��o do jogo em um determinado ponto. */
class Situacao {
public:
    /** Cria a situa��o em que n�o h� nada a ser adicionado e n�o h� pe�a caindo.
     * @param tabuleiro o tabuleiro
     * @param placar    o placar atual
     */
    Situacao(const piece::Board& tabuleiro,
          const score::ScoreBoard& placar);
    /** Cria a situa��o em que n�o h� pe�a caindo.
     * @param tabuleiro o tabuleiro
     * @param placar    o placar atual
     * @param caindo    a pe�a caindo
     * @param posicao   a posi��o atual da pe�a
     * @param proxima   a pr�xima pe�a
     */
    Situacao(const piece::Board& tabuleiro,
          const score::ScoreBoard& placar,
          const piece::Piece& caindo,
          const piece::PiecePosition& posicao,
          const piece::Piece& proxima);
    /** Cria a situa��o em que n�o h� nada a ser adicionado e n�o h� pe�a caindo.
     * @param tabuleiro o tabuleiro
     * @param placar    o placar atual
     * @param lista     a lista de pe�as a serem eliminadas
     * @param proxima   a pr�xima pe�a
     */
    Situacao(const piece::Board& tabuleiro,
          const score::ScoreBoard& placar,
          const ListaEliminacao& lista,
          const piece::Piece& proxima);
    const piece::Board& tabuleiro() const { return tabuleiro_; }
    const score::ScoreBoard& placar() const { return placar_; }
    /** @return se h� uma pe�a caindo no tabuleiro. */
    bool temPeca() const { return peca_.get() != NULL; }
    /** @return a posi��o da pe�a que est� caindo no tabuleiro.
     * @throw std::logic_error � lan�ada caso n�o haja pe�a caindo no tabuleiro
     */
    const piece::PiecePosition& posicaoPeca() const;
    /** @return a pe�a que est� caindo no tabuleiro.
     * @throw std::logic_error � lan�ada caso n�o haja pe�a caindo no tabuleiro
     */
    const piece::Piece& piece() const;
    /** @return a lista de casas a serem eliminadas. */
    const ListaEliminacao& eliminacao() const { return eliminacao_; }
    /** @return se h� uma pr�xima pe�a a ser colocada no tabuleiro. */
    bool temProxima() const { return proxima_.get() != NULL; }
    /** @return a pr�xima pe�a a ser colocada no tabuleiro.
     * @throw std::logic_error � lan�ada caso n�o haja pr�xima pe�a
     */
    const piece::Piece& proxima() const;

private:
    typedef std::unique_ptr<piece::PiecePosition> PosicaoPtr;
    piece::Board tabuleiro_;     ///< o tabuleiro
    score::ScoreBoard placar_;   ///< o placar atual
    piece::PiecePtr peca_;       ///< a piece caindo no tabuleiro
    PosicaoPtr posicaoPeca_;     ///< a posi��o em que est� a pe�a caindo no tabuleiro
    ListaEliminacao eliminacao_; ///< a lista de elimina��o
    piece::PiecePtr proxima_;    ///< a pr�xima pe�a a ser colocada no tabuleiro
};

bool operator==(const Situacao& lhs, const Situacao& rhs);
bool operator!=(const Situacao& lhs, const Situacao& rhs);
}
