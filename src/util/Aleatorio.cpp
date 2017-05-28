
#include "Aleatorio.h"

namespace util {

std::mt19937 Aleatorio::engine_(std::random_device {}());
Aleatorio::MapaDist Aleatorio::dists_;

/** @return a distribuição associada a N, caso não exista, cria.
 * @param mapa  o mapa de distribuições
 * @param N     o limite dos valores
 */
Aleatorio::Distribuicao & distribuicao(Aleatorio::MapaDist & mapa,
                                       const size_t N) {
    const auto it = mapa.find(N);
    if (it != mapa.end())
        return it->second;
    const auto inserido = mapa.insert(std::make_pair(N, Aleatorio::Distribuicao(0, N)));
    return inserido.first->second;
}

size_t Aleatorio::gera(const size_t N) {
    if (N == 0)
        return 0;
    Distribuicao & dist = distribuicao(dists_, N);
    return dist(engine_);
}


}
