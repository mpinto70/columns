
#ifndef ALEATORIO_H_mhpa
#define ALEATORIO_H_mhpa

#include <map>
#include <random>

/** namespace das classes utilit�rias gen�ricas do jogo. */
namespace util {
/** Respons�vel por gerar n�meros aleat�rios. */
class Aleatorio {
    public:
        /** distribui��o uniforme. */
        typedef std::uniform_int_distribution<size_t> Distribuicao;
        /** mapa de distribui��es uniformes em N. */
        typedef std::map<size_t, Distribuicao> MapaDist;
        /** construtor deletado. */
        Aleatorio() = delete;
        /** destrutor deletado. */
        ~Aleatorio() = delete;
        /** @return n�mero aleat�rio [0,N].
         * @param N     o limite do valor a ser gerado
         */
        static size_t gera(size_t N);
    private:
        static std::mt19937 engine_;    ///< gerador de n�meros rand�micos
        static MapaDist dists_;         ///< mapa de distribui��es uniformes
};

}

#endif
