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
/** Respons�vel por registrar a situa��o do jogo em um determinado ponto. */
class Situacao {
public:
    /** Cria a situa��o em que n�o h� nada a ser adicionado e n�o h� pe�a caindo.
     * @param tabuleiro o tabuleiro
     * @param placar    o placar atual
     */
    Situacao(const peca::Tabuleiro& tabuleiro,
          const pontuacao::Placar& placar);
    /** Cria a situa��o em que n�o h� pe�a caindo.
     * @param tabuleiro o tabuleiro
     * @param placar    o placar atual
     * @param caindo    a pe�a caindo
     * @param posicao   a posi��o atual da pe�a
     * @param proxima   a pr�xima pe�a
     */
    Situacao(const peca::Tabuleiro& tabuleiro,
          const pontuacao::Placar& placar,
          const peca::Tile& caindo,
          const peca::PosicaoPeca& posicao,
          const peca::Tile& proxima);
    /** Cria a situa��o em que n�o h� nada a ser adicionado e n�o h� pe�a caindo.
     * @param tabuleiro o tabuleiro
     * @param placar    o placar atual
     * @param lista     a lista de pe�as a serem eliminadas
     * @param proxima   a pr�xima pe�a
     */
    Situacao(const peca::Tabuleiro& tabuleiro,
          const pontuacao::Placar& placar,
          const ListaEliminacao& lista,
          const peca::Tile& proxima);
    const peca::Tabuleiro& tabuleiro() const { return tabuleiro_; }
    const pontuacao::Placar& placar() const { return placar_; }
    /** @return se h� uma pe�a caindo no tabuleiro. */
    bool temPeca() const { return peca_.get() != NULL; }
    /** @return a posi��o da pe�a que est� caindo no tabuleiro.
     * @throw std::logic_error � lan�ada caso n�o haja pe�a caindo no tabuleiro
     */
    const peca::PosicaoPeca& posicaoPeca() const;
    /** @return a pe�a que est� caindo no tabuleiro.
     * @throw std::logic_error � lan�ada caso n�o haja pe�a caindo no tabuleiro
     */
    const peca::Tile& peca() const;
    /** @return a lista de casas a serem eliminadas. */
    const ListaEliminacao& eliminacao() const { return eliminacao_; }
    /** @return se h� uma pr�xima pe�a a ser colocada no tabuleiro. */
    bool temProxima() const { return proxima_.get() != NULL; }
    /** @return a pr�xima pe�a a ser colocada no tabuleiro.
     * @throw std::logic_error � lan�ada caso n�o haja pr�xima pe�a
     */
    const peca::Tile& proxima() const;

private:
    typedef std::unique_ptr<peca::PosicaoPeca> PosicaoPtr;
    peca::Tabuleiro tabuleiro_;  ///< o tabuleiro
    pontuacao::Placar placar_;   ///< o placar atual
    peca::TilePtr peca_;         ///< a peca caindo no tabuleiro
    PosicaoPtr posicaoPeca_;     ///< a posi��o em que est� a pe�a caindo no tabuleiro
    ListaEliminacao eliminacao_; ///< a lista de elimina��o
    peca::TilePtr proxima_;      ///< a pr�xima pe�a a ser colocada no tabuleiro
};

bool operator==(const Situacao& lhs, const Situacao& rhs);
bool operator!=(const Situacao& lhs, const Situacao& rhs);
}
