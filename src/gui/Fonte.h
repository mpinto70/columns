
#ifndef FONTE_H_mhpa
#define FONTE_H_mhpa

#include <cstdint>
#include <string>

namespace gui {

/** Responsável por representar uma fonte. */
class Fonte {
    public:
        /** Cria uma fonte informando o nome e o tamanho
         * @param nome      o nome da fonte (caminho para o arquivo)
         * @param tamanho   o tamanho da fonte
         */
        Fonte(const std::string & nome,
              unsigned char tamanho);
        /** Substitui o conteúdo do objeto atual pelo conteúdo de outro objeto.
         * @param rhs o outro objeto
         */
        void swap(Fonte & rhs);
        /** @return o nome da fonte. */
        const std::string & nome() const { return nome_; }
        /** @return o tamanho da fonte. */
        unsigned char tamanho() const { return tamanho_; }
    private:
        std::string nome_;      ///< o nome da fonte (caminho para o arquivo)
        unsigned char tamanho_; ///< o tamanho da fonte
};

/** @return se as duas fontes são iguais.
 * @param lhs o objeto à esquerda do operador
 * @param rhs o objeto à direita do operador
 */
bool operator == (const Fonte & lhs, const Fonte & rhs);

}
#endif
