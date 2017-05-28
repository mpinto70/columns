
#include "testeAleatorio.h"
#include "util/Aleatorio.h"

#include <stdexcept>
#include <utility>

namespace util {
namespace tst {

std::vector<size_t> criaVetor(const size_t N) {
    std::vector<size_t> res;
    for (size_t i = 0; i < 2 * N + 100; ++i) {
        res.push_back(Aleatorio::gera(N));
    }
    return res;
}

static void confereGeracao(const int line,
                           const size_t N) {
    const auto v1 = criaVetor(N);
    const auto v2 = criaVetor(N);
    const std::set<size_t> gerados(v1.begin(), v1.end());
    TSM_ASSERT(line, gerados.size() > 0);
    TSM_ASSERT(line, gerados.size() <= N + 1);
    TSM_ASSERT(line, *gerados.begin() >= 0);
    TSM_ASSERT(line, *gerados.rbegin() <= N);
    TSM_ASSERT_DIFFERS(line, v1, v2);
}

void TesteAleatorio::testeGeracao() {
    for (size_t i = 0; i < 10000; ++i)
        confereGeracao(__LINE__, 1);

    confereGeracao(__LINE__, 2);
    confereGeracao(__LINE__, 20);
    confereGeracao(__LINE__, 200);
    confereGeracao(__LINE__, 2000);
    confereGeracao(__LINE__, 20000);

    for (size_t i = 0; i < 200; ++i) {
        TSM_ASSERT_EQUALS(i, Aleatorio::gera(0), 0);
    }
}

}
}
