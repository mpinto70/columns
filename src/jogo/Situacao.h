#pragma once

#include "peca/PosicaoPeca.h"
#include "peca/Tabuleiro.h"
#include "pontuacao/Placar.h"
#include <memory>
#include <peca/Tile.h>

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
    Situacao(const peca::Tabuleiro& tabuleiro,
          const pontuacao::Placar& placar);
    /** Cria a situação em que não há peça caindo.
     * @param tabuleiro o tabuleiro
     * @param placar    o placar atual
     * @param caindo    a peça caindo
     * @param posicao   a posição atual da peça
     * @param proxima   a próxima peça
     */
    Situacao(const peca::Tabuleiro& tabuleiro,
          const pontuacao::Placar& placar,
          const peca::Tile& caindo,
          const peca::PosicaoPeca& posicao,
          const peca::Tile& proxima);
    /** Cria a situação em que não há nada a ser adicionado e não há peça caindo.
     * @param tabuleiro o tabuleiro
     * @param placar    o placar atual
     * @param lista     a lista de peças a serem eliminadas
     * @param proxima   a próxima peça
     */
    Situacao(const peca::Tabuleiro& tabuleiro,
          const pontuacao::Placar& placar,
          const ListaEliminacao& lista,
          const peca::Tile& proxima);
    const peca::Tabuleiro& tabuleiro() const { return tabuleiro_; }
    const pontuacao::Placar& placar() const { return placar_; }
    /** @return se há uma peça caindo no tabuleiro. */
    bool temPeca() const { return peca_.get() != NULL; }
    /** @return a posição da peça que está caindo no tabuleiro.
     * @throw std::logic_error é lançada caso não haja peça caindo no tabuleiro
     */
    const peca::PosicaoPeca& posicaoPeca() const;
    /** @return a peça que está caindo no tabuleiro.
     * @throw std::logic_error é lançada caso não haja peça caindo no tabuleiro
     */
    const peca::Tile& peca() const;
    /** @return a lista de casas a serem eliminadas. */
    const ListaEliminacao& eliminacao() const { return eliminacao_; }
    /** @return se há uma próxima peça a ser colocada no tabuleiro. */
    bool temProxima() const { return proxima_.get() != NULL; }
    /** @return a próxima peça a ser colocada no tabuleiro.
     * @throw std::logic_error é lançada caso não haja próxima peça
     */
    const peca::Tile& proxima() const;

private:
    typedef std::unique_ptr<peca::PosicaoPeca> PosicaoPtr;
    peca::Tabuleiro tabuleiro_;  ///< o tabuleiro
    pontuacao::Placar placar_;   ///< o placar atual
    peca::TilePtr peca_;         ///< a peca caindo no tabuleiro
    PosicaoPtr posicaoPeca_;     ///< a posição em que está a peça caindo no tabuleiro
    ListaEliminacao eliminacao_; ///< a lista de eliminação
    peca::TilePtr proxima_;      ///< a próxima peça a ser colocada no tabuleiro
};

bool operator==(const Situacao& lhs, const Situacao& rhs);
bool operator!=(const Situacao& lhs, const Situacao& rhs);
}
