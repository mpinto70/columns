#pragma once

#include "gui/Cor.h"
#include <memory>
#include <vector>

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
    Peca(const gui::Cor(&cores)[TAMANHO_PECA]);
    Peca(const std::vector<gui::Cor>& cores);
    Peca(const Peca& rhs);
    Peca& operator = (const Peca& rhs);
    void swap(Peca& rhs);
    /** @return a cor do quadradinho indexado por \p i.
     * @param i o �ndice (0 <= i <= 2)
     * @throws std::invalid_argument � lan�ada caso \p i esteja fora dos limites
     */
    const gui::Cor& operator[](unsigned char i) const;
    void rolaParaCima();
    void rolaParaBaixo();
    /** @return uma pe�a com cores aleat�rias a partir das cores passadas.
     * @param coresPossiveis as cores que ser�o sorteadas para criar a pe�a.
     */
    static Peca cria(const std::vector<gui::Cor>& coresPossiveis);
private:
    gui::Cor cores_[TAMANHO_PECA];  ///< as cores de cada quadradinho da pe�a
};

bool operator == (const Peca& lhs, const Peca& rhs);
bool operator != (const Peca& lhs, const Peca& rhs);
typedef std::unique_ptr<Peca> PecaPtr;
}
