#pragma once

#include "jogo/Situacao.h"
#include "peca/Peca.h"
#include "peca/PosicaoPeca.h"
#include "peca/Tabuleiro.h"
#include <memory>

namespace jogo {
/** Respons�vel controlar a intera��o com um tabuleiro:
 * \li informar se � poss�vel incluir mais pe�as;
 * \li colocar uma nova pe�a para cair;
 * \li deslocar a pe�a para esquerda e para direita;
 * \li rolar a pe�a;
 * \li indicar e realizar a elimina��o de pe�as.
 */
class ControladorTabuleiro {
public:
    /**
     * @param tabuleiro o tabuleiro em que o controlador vai gerenciar a queda da pe�a
     * @param maxSubLinha o m�ximo de subdivis�o do passo da pe�a
     */
    ControladorTabuleiro(const peca::Tabuleiro& tabuleiro,
          uint16_t maxSubLinha);
    ControladorTabuleiro(const ControladorTabuleiro&) = delete;
    ControladorTabuleiro& operator=(const ControladorTabuleiro&) = delete;
    const peca::Tabuleiro& tabuleiro() const { return tabuleiro_; }
    /** Adiciona a peca \p peca ao tabuleiro
     * @param peca a pe�a sendo adicionada ao tabuleiro
     * @return true se foi poss�vel criar a pe�a
     * @return false se n�o foi poss�vel criar a pe�a
     * @throw std::logic_error � lan�ada caso haja pe�a caindo no tabuleiro
     */
    bool adicionaPeca(const peca::Peca& peca);
    /** @return se h� uma pe�a caindo no tabuleiro. */
    bool temPeca() const { return peca_.get() != NULL; }
    /** @return a posi��o da pe�a que est� caindo no tabuleiro.
     * @throw std::logic_error � lan�ada caso n�o haja pe�a caindo no tabuleiro
     */
    const peca::PosicaoPeca& posicaoPeca() const;
    /** @return a pe�a que est� caindo no tabuleiro.
     * @throw std::logic_error � lan�ada caso n�o haja pe�a caindo no tabuleiro
     */
    const peca::Peca& peca() const;
    /** Faz a pe�a dar um passo para baixo. */
    void passo();
    /** Move a pe�a uma coluna para a esquerda. */
    void moveEsquerda();
    /** Move a pe�a uma coluna para a direita. */
    void moveDireita();
    /** Rola a pe�a para cima. */
    void rolaParaCima();
    /** Rola a pe�a para baixo. */
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
    PosicaoPtr posicaoPeca_;                  ///< a posi��o em que est� a pe�a caindo no tabuleiro
    const uint16_t maxSubLinha_;              ///< tamanho do quadradinho da pe�a
    const std::vector<gui::Color> possiveis_; ///< cores poss�veis para as pe�as
    /** @return se � poss�vel mover a pe�a para a \p coluna.
     * @param coluna o n�mero da coluna de destino
     */
    bool podeMoverPara(uint16_t coluna) const;
    /** @return a coluna a ser inserida a pe�a.
     * @attention se n�o houver coluna retorna a largura do tabuleiro
     */
    uint16_t determinaColuna() const;
    /** @return se � poss�vel coloar a pe�a na coluna \p coluna.
     * @param coluna o n�mero da coluna de destino
     */
    bool podeColocarPeca(uint16_t coluna) const;
    /** @return se a pe�a que est� caindo chegou ao fim de seu trajeto. */
    bool atingiuFim() const;
    /** @return se a pe�a colocada em (\p coluna, \p linha ) deve ser eliminada.
     * @param coluna o n�mero da coluna sendo verificada
     * @param linha o n�mero da linha sendo verificada
     */
    bool deveEliminar(uint16_t coluna, uint16_t linha) const;
};
}
