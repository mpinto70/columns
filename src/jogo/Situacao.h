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
/** Responsável por registrar a situação do jogo em um determinado ponto. */
class Situacao {
public:
    /** Cria a situação em que não há nada a ser adicionado e não há peça caindo.
     * @param tabuleiro o tabuleiro
     * @param placar    o placar atual
     */
    Situacao(const piece::Board& tabuleiro,
          const score::ScoreBoard& placar);
    /** Cria a situação em que não há peça caindo.
     * @param tabuleiro o tabuleiro
     * @param placar    o placar atual
     * @param caindo    a peça caindo
     * @param posicao   a posição atual da peça
     * @param proxima   a próxima peça
     */
    Situacao(const piece::Board& tabuleiro,
          const score::ScoreBoard& placar,
          const piece::Piece& caindo,
          const piece::PiecePosition& posicao,
          const piece::Piece& proxima);
    /** Cria a situação em que não há nada a ser adicionado e não há peça caindo.
     * @param tabuleiro o tabuleiro
     * @param placar    o placar atual
     * @param lista     a lista de peças a serem eliminadas
     * @param proxima   a próxima peça
     */
    Situacao(const piece::Board& tabuleiro,
          const score::ScoreBoard& placar,
          const ListaEliminacao& lista,
          const piece::Piece& proxima);
    const piece::Board& tabuleiro() const { return tabuleiro_; }
    const score::ScoreBoard& placar() const { return placar_; }
    /** @return se há uma peça caindo no tabuleiro. */
    bool temPeca() const { return peca_.get() != NULL; }
    /** @return a posição da peça que está caindo no tabuleiro.
     * @throw std::logic_error é lançada caso não haja peça caindo no tabuleiro
     */
    const piece::PiecePosition& posicaoPeca() const;
    /** @return a peça que está caindo no tabuleiro.
     * @throw std::logic_error é lançada caso não haja peça caindo no tabuleiro
     */
    const piece::Piece& piece() const;
    /** @return a lista de casas a serem eliminadas. */
    const ListaEliminacao& eliminacao() const { return eliminacao_; }
    /** @return se há uma próxima peça a ser colocada no tabuleiro. */
    bool temProxima() const { return proxima_.get() != NULL; }
    /** @return a próxima peça a ser colocada no tabuleiro.
     * @throw std::logic_error é lançada caso não haja próxima peça
     */
    const piece::Piece& proxima() const;

private:
    typedef std::unique_ptr<piece::PiecePosition> PosicaoPtr;
    piece::Board tabuleiro_;     ///< o tabuleiro
    score::ScoreBoard placar_;   ///< o placar atual
    piece::PiecePtr peca_;       ///< a piece caindo no tabuleiro
    PosicaoPtr posicaoPeca_;     ///< a posição em que está a peça caindo no tabuleiro
    ListaEliminacao eliminacao_; ///< a lista de eliminação
    piece::PiecePtr proxima_;    ///< a próxima peça a ser colocada no tabuleiro
};

bool operator==(const Situacao& lhs, const Situacao& rhs);
bool operator!=(const Situacao& lhs, const Situacao& rhs);
}
