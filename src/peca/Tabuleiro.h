
#ifndef TABULEIRO_H_mhpa
#define TABULEIRO_H_mhpa

#include "gui/Cor.h"
#include "peca/Peca.h"
#include <memory>
#include <vector>

namespace peca {
/** Respons�vel por representar o tabuleiro do jogo. */
class Tabuleiro {
    public:
        /** Cria um tabuleiro vazio com dimens�es l X h.
         * @param l largura do tabuleiro em quadradinhos
         * @param h altura do tabuleiro em quadradinhos
         * @param cor a cor do fundo do tabuleiro
         */
        Tabuleiro(uint16_t l, uint16_t h, const gui::Cor & cor);
        /** Cria uma c�pia do tabuleiro
         * @param rhs o tabuleiro sendo copiado
         */
        Tabuleiro(const Tabuleiro & rhs);
        /** @return as casas do tabuleiro. */
        const std::vector<gui::Cor> & casas() const { return casas_; }
        /** Copia o tabuleiro desprezando
         * @param rhs o tabuleiro sendo copiado
         * @return uma refer�ncia ao novo objeto
         */
        Tabuleiro & operator = (const Tabuleiro & rhs);
        /** @return o elemento na posi��o (c, l).
         * @param c o �ndice da coluna a ser retornada
         * @param l o �ndice da linha a ser retornada
         */
        const gui::Cor & at(uint16_t c, uint16_t l) const;
        /** @return o elemento na posi��o (c, l) para escrita.
         * @param c o �ndice da coluna a ser retornada
         * @param l o �ndice da linha a ser retornada
         */
        gui::Cor & at(uint16_t c, uint16_t l);
        /** @return a cor de fundo. */
        const gui::Cor & cor() const { return cor_; }
        /** @return a largura do tabuleiro em quadradinhos. */
        uint16_t largura() const { return largura_; }
        /** @return a altura do tabuleiro em quadradinhos. */
        uint16_t altura() const { return altura_; }
        /** Elimina a pe�a na posi��o (c, l) fazendo com que as pe�as acima dela caiam.
         * @param c o �ndice da coluna a ser eliminada
         * @param l o �ndice da linha a ser eliminada
         */
        void elimina(uint16_t c, uint16_t l);
    private:
        std::vector<gui::Cor> casas_;   ///< o tabuleiro
        gui::Cor cor_;                  ///< cor de fundo do tabuleiro
        uint16_t largura_;              ///< a largura do tabuleiro
        uint16_t altura_;               ///< a altura do tabuleiro
};

/** @return se os dois tabuleiros s�o iguais.
 * @param lhs o tabuleiro � esquerda do sinal
 * @param rhs o tabuleiro � direita do sinal
 */
bool operator == (const Tabuleiro & lhs, const Tabuleiro & rhs);

}

#endif
