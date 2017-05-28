
#ifndef PECA_H_mhpa
#define PECA_H_mhpa

#include "gui/Cor.h"
#include <memory>
#include <vector>

/** namespace das entidades relacionadas às peças. */
namespace peca {
/** a quantidade de quadradinhos na peça. */
constexpr unsigned char TAMANHO_PECA = 3;
/** Responsável por representar uma peça composta de TAMANHO_PECA quadradinhos coloridos.
    \verbatim
                                        Ex: Peca(gui::Vermelho, gui::Azul, gui:Verde)
     ___                                         ___
    |   |                                       |   |
    | 0 | <--- cor 0                            | 0 | <--- Vermelho
    |___|                                       |___|
    |   |                                       |   |
    | 1 | <--- cor 1                            | 1 | <--- Azul
    |___|                                       |___|
    |   |                                       |   |
    | 2 | <--- cor 2                            | 2 | <--- Verde
    |___|                                       |___|
    \endverbatim
 */
class Peca {
    public:
        /** Cria o objeto informando as cores dos quadradinhos.
         * @param cores as cores dos quadradinhos
         */
        Peca(const gui::Cor(&cores)[TAMANHO_PECA]);
        /** Cria o objeto informando as cores dos quadradinhos.
         * @param cores as cores dos quadradinhos
         */
        Peca(const std::vector<gui::Cor>& cores);
        /** Cria uma cópia de \b rhs.
         * @param rhs a peça sendo copiada
         */
        Peca(const Peca & rhs);
        /** Copia o conteúdo de \b rhs.
         * @param rhs a peça sendo copiada
         * @return referência ao objeto criado
         */
        Peca & operator = (const Peca & rhs);
        /** Troca o conteúdo com \b rhs.
         * @param rhs a peça sendo trocada
         */
        void swap(Peca & rhs);
        /** @return a cor do quadradinho indexado por \b i.
         * @param i o índice (0 <= i <= 2)
         * @throws std::invalid_argument é lançada caso \b i esteja fora dos limites
         */
        const gui::Cor & operator[](unsigned char i) const;
        /** Rola as cores para cima. */
        void rolaParaCima();
        /** Rola as cores para baixo. */
        void rolaParaBaixo();
        /** @return uma peça com cores aleatórias a partir das cores passadas.
         * @param coresPossiveis as cores que serão sorteadas para criar a peça.
         */
        static Peca cria(const std::vector<gui::Cor> & coresPossiveis);
    private:
        gui::Cor cores_[TAMANHO_PECA];  ///< as cores de cada quadradinho da peça
};

/** @return se as duas peças são iguais.
 * @param lhs o objeto à esquerda da igualdade
 * @param rhs o objeto à direita da igualdade
 */
bool operator == (const Peca & lhs, const Peca & rhs);
/** ponteiro de Peca. */
typedef std::unique_ptr<Peca> PecaPtr;
}
#endif
