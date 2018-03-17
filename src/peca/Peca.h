#pragma once

#include "gui/Color.h"

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
    explicit Peca(const gui::Color (&cores)[TAMANHO_PECA]);
    explicit Peca(const std::vector<gui::Color>& cores);
    /** @return a cor do quadradinho indexado por \p i.
     * @param i o �ndice (0 <= i <= 2)
     * @throws std::invalid_argument � lan�ada caso \p i esteja fora dos limites
     */
    const gui::Color& operator[](unsigned char i) const;
    void rolaParaCima();
    void rolaParaBaixo();
    /** @return uma pe�a com cores aleat�rias a partir das cores passadas.
     * @param coresPossiveis as cores que ser�o sorteadas para criar a pe�a.
     */
    static Peca cria(const std::vector<gui::Color>& coresPossiveis);

private:
    gui::Color cores_[TAMANHO_PECA]; ///< as cores de cada quadradinho da pe�a
};

bool operator==(const Peca& lhs, const Peca& rhs);
bool operator!=(const Peca& lhs, const Peca& rhs);
typedef std::unique_ptr<Peca> PecaPtr;
}
