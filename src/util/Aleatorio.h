
#ifndef ALEATORIO_H_mhpa
#define ALEATORIO_H_mhpa

#include <map>
#include <random>

/** namespace das classes utilitárias genéricas do jogo. */
namespace util {
/** Responsável por gerar números aleatórios. */
class Aleatorio {
    public:
        /** distribuição uniforme. */
        typedef std::uniform_int_distribution<size_t> Distribuicao;
        /** mapa de distribuições uniformes em N. */
        typedef std::map<size_t, Distribuicao> MapaDist;
        /** construtor deletado. */
        Aleatorio() = delete;
        /** destrutor deletado. */
        ~Aleatorio() = delete;
        /** @return número aleatório [0,N].
         * @param N     o limite do valor a ser gerado
         */
        static size_t gera(size_t N);
    private:
        static std::mt19937 engine_;    ///< gerador de números randômicos
        static MapaDist dists_;         ///< mapa de distribuições uniformes
};

}

#endif
