#pragma once

#include <map>
#include <random>

/** utility classes namespace. */
namespace util {
/** Responsible for generating random numbers in interval [0,N]. */
class Random {
public:
    using Distribution = std::uniform_int_distribution<size_t>;
    using DistMap = std::map<size_t, Distribution>;
    Random() = delete;
    ~Random() = delete;
    /** @return random number in [0,N].
     * @param N upper limit to be generated
     */
    static size_t get(size_t N);

private:
    static std::mt19937 engine_; ///< random number engine
    static DistMap dists_;       ///< uniform distribution map
};
}
