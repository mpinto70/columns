#pragma once

#include "jogo/Situacao.h"
#include "peca/Peca.h"
#include "peca/PosicaoPeca.h"
#include "peca/Tabuleiro.h"
#include <memory>

namespace jogo {
/** Responsável controlar a interação com um tabuleiro:
 * \li informar se é possível incluir mais peças;
 * \li colocar uma nova peça para cair;
 * \li deslocar a peça para esquerda e para direita;
 * \li rolar a peça;
 * \li indicar e realizar a eliminação de peças.
 */
class ControladorTabuleiro {
public:
    /**
     * @param tabuleiro o tabuleiro em que o controlador vai gerenciar a queda da peça
     * @param maxSubLinha o máximo de subdivisão do passo da peça
     */
    ControladorTabuleiro(const peca::Tabuleiro& tabuleiro,
          uint16_t maxSubLinha);
    ControladorTabuleiro(const ControladorTabuleiro&) = delete;
    ControladorTabuleiro& operator=(const ControladorTabuleiro&) = delete;
    const peca::Tabuleiro& tabuleiro() const { return tabuleiro_; }
    /** Adiciona a peca \p peca ao tabuleiro
     * @param peca a peça sendo adicionada ao tabuleiro
     * @return true se foi possível criar a peça
     * @return false se não foi possível criar a peça
     * @throw std::logic_error é lançada caso haja peça caindo no tabuleiro
     */
    bool adicionaPeca(const peca::Peca& peca);
    /** @return se há uma peça caindo no tabuleiro. */
    bool temPeca() const { return peca_.get() != NULL; }
    /** @return a posição da peça que está caindo no tabuleiro.
     * @throw std::logic_error é lançada caso não haja peça caindo no tabuleiro
     */
    const peca::PosicaoPeca& posicaoPeca() const;
    /** @return a peça que está caindo no tabuleiro.
     * @throw std::logic_error é lançada caso não haja peça caindo no tabuleiro
     */
    const peca::Peca& peca() const;
    /** Faz a peça dar um passo para baixo. */
    void passo();
    /** Move a peça uma coluna para a esquerda. */
    void moveEsquerda();
    /** Move a peça uma coluna para a direita. */
    void moveDireita();
    /** Rola a peça para cima. */
    void rolaParaCima();
    /** Rola a peça para baixo. */
    void rolaParaBaixo();
    /** @return a lista de casas a serem eliminadas. */
    ListaEliminacao determinaEliminacao() const;
    /** Elimina as casas.
     * @param casas a lista de casas a serem eliminadas
     */
    void elimina(const ListaEliminacao& casas);
    Situacao situacao() const;

private:
    typedef std::unique_ptr<peca::PosicaoPeca> PosicaoPtr;
    peca::Tabuleiro tabuleiro_;               ///< o tabuleiro
    peca::PecaPtr peca_;                      ///< a peca caindo no tabuleiro
    PosicaoPtr posicaoPeca_;                  ///< a posição em que está a peça caindo no tabuleiro
    const uint16_t maxSubLinha_;              ///< tamanho do quadradinho da peça
    const std::vector<gui::Color> possiveis_; ///< cores possíveis para as peças
    /** @return se é possível mover a peça para a \p coluna.
     * @param coluna o número da coluna de destino
     */
    bool podeMoverPara(uint16_t coluna) const;
    /** @return a coluna a ser inserida a peça.
     * @attention se não houver coluna retorna a largura do tabuleiro
     */
    uint16_t determinaColuna() const;
    /** @return se é possível coloar a peça na coluna \p coluna.
     * @param coluna o número da coluna de destino
     */
    bool podeColocarPeca(uint16_t coluna) const;
    /** @return se a peça que está caindo chegou ao fim de seu trajeto. */
    bool atingiuFim() const;
    /** @return se a peça colocada em (\p coluna, \p linha ) deve ser eliminada.
     * @param coluna o número da coluna sendo verificada
     * @param linha o número da linha sendo verificada
     */
    bool deveEliminar(uint16_t coluna, uint16_t linha) const;
};
}
