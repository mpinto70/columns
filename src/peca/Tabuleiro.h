
#ifndef TABULEIRO_H_mhpa
#define TABULEIRO_H_mhpa

#include "gui/Cor.h"
#include "peca/Peca.h"
#include <memory>
#include <vector>

namespace peca {
/** Responsável por representar o tabuleiro do jogo. */
class Tabuleiro {
    public:
        /** Cria um tabuleiro vazio com dimensões l X h.
         * @param l largura do tabuleiro em quadradinhos
         * @param h altura do tabuleiro em quadradinhos
         * @param cor a cor do fundo do tabuleiro
         */
        Tabuleiro(uint16_t l, uint16_t h, const gui::Cor & cor);
        /** Cria uma cópia do tabuleiro
         * @param rhs o tabuleiro sendo copiado
         */
        Tabuleiro(const Tabuleiro & rhs);
        /** @return as casas do tabuleiro. */
        const std::vector<gui::Cor> & casas() const { return casas_; }
        /** Copia o tabuleiro desprezando
         * @param rhs o tabuleiro sendo copiado
         * @return uma referência ao novo objeto
         */
        Tabuleiro & operator = (const Tabuleiro & rhs);
        /** @return o elemento na posição (c, l).
         * @param c o índice da coluna a ser retornada
         * @param l o índice da linha a ser retornada
         */
        const gui::Cor & at(uint16_t c, uint16_t l) const;
        /** @return o elemento na posição (c, l) para escrita.
         * @param c o índice da coluna a ser retornada
         * @param l o índice da linha a ser retornada
         */
        gui::Cor & at(uint16_t c, uint16_t l);
        /** @return a cor de fundo. */
        const gui::Cor & cor() const { return cor_; }
        /** @return a largura do tabuleiro em quadradinhos. */
        uint16_t largura() const { return largura_; }
        /** @return a altura do tabuleiro em quadradinhos. */
        uint16_t altura() const { return altura_; }
        /** Elimina a peça na posição (c, l) fazendo com que as peças acima dela caiam.
         * @param c o índice da coluna a ser eliminada
         * @param l o índice da linha a ser eliminada
         */
        void elimina(uint16_t c, uint16_t l);
    private:
        std::vector<gui::Cor> casas_;   ///< o tabuleiro
        gui::Cor cor_;                  ///< cor de fundo do tabuleiro
        uint16_t largura_;              ///< a largura do tabuleiro
        uint16_t altura_;               ///< a altura do tabuleiro
};

/** @return se os dois tabuleiros são iguais.
 * @param lhs o tabuleiro à esquerda do sinal
 * @param rhs o tabuleiro à direita do sinal
 */
bool operator == (const Tabuleiro & lhs, const Tabuleiro & rhs);

}

#endif
