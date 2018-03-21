#include "Random.h"

namespace util {

std::mt19937 Random::engine_(std::random_device{}());
Random::DistMap Random::dists_;

namespace {
/** @return the distribution associated to N, if it does not exist yet, create it.
 * @param map   distribution map
 * @param N     upper limit of values
 */
Random::Distribution& distribution(Random::DistMap& map, const size_t N) {
    const auto it = map.find(N);
    if (it != map.end()) {
        return it->second;
    }
    const auto inserted = map.insert(std::make_pair(N, Random::Distribution(0, N)));
    return inserted.first->second;
}
}

size_t Random::get(const size_t N) {
    if (N == 0) {
        return 0;
    }
    Distribution& dist = distribution(dists_, N);
    return dist(engine_);
}
}
