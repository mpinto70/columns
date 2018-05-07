#pragma once

#include <map>
#include <random>

/** utility classes namespace. */
namespace util {
/** Responsible for generating random numbers in interval [0,N]. */
class Random {
public:
    Random() = delete;
    ~Random() = delete;
    /** @return random number in [0,N].
     * @param N upper limit to be generated
     */
    static size_t get(size_t N);
};
}
