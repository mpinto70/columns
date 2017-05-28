
#ifndef PECA_H_mhpa
#define PECA_H_mhpa

#include "gui/Cor.h"
#include <memory>
#include <vector>

/** namespace das entidades relacionadas �s pe�as. */
namespace peca {
/** a quantidade de quadradinhos na pe�a. */
constexpr unsigned char TAMANHO_PECA = 3;
/** Respons�vel por representar uma pe�a composta de TAMANHO_PECA quadradinhos coloridos.
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
        /** Cria uma c�pia de \b rhs.
         * @param rhs a pe�a sendo copiada
         */
        Peca(const Peca & rhs);
        /** Copia o conte�do de \b rhs.
         * @param rhs a pe�a sendo copiada
         * @return refer�ncia ao objeto criado
         */
        Peca & operator = (const Peca & rhs);
        /** Troca o conte�do com \b rhs.
         * @param rhs a pe�a sendo trocada
         */
        void swap(Peca & rhs);
        /** @return a cor do quadradinho indexado por \b i.
         * @param i o �ndice (0 <= i <= 2)
         * @throws std::invalid_argument � lan�ada caso \b i esteja fora dos limites
         */
        const gui::Cor & operator[](unsigned char i) const;
        /** Rola as cores para cima. */
        void rolaParaCima();
        /** Rola as cores para baixo. */
        void rolaParaBaixo();
        /** @return uma pe�a com cores aleat�rias a partir das cores passadas.
         * @param coresPossiveis as cores que ser�o sorteadas para criar a pe�a.
         */
        static Peca cria(const std::vector<gui::Cor> & coresPossiveis);
    private:
        gui::Cor cores_[TAMANHO_PECA];  ///< as cores de cada quadradinho da pe�a
};

/** @return se as duas pe�as s�o iguais.
 * @param lhs o objeto � esquerda da igualdade
 * @param rhs o objeto � direita da igualdade
 */
bool operator == (const Peca & lhs, const Peca & rhs);
/** ponteiro de Peca. */
typedef std::unique_ptr<Peca> PecaPtr;
}
#endif
