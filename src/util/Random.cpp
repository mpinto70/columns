#include "Random.h"

namespace util {

size_t Random::get(const size_t N) {
    static thread_local std::mt19937 engine(std::random_device{}());

    if (N == 0) {
        return 0;
    }
    std::uniform_int_distribution<size_t> dist(0, N);
    return dist(engine);
}
}
