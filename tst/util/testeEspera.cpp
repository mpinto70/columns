
#include "testeEspera.h"

#include "util/Espera.h"

#include <sys/time.h>
#include <utility>

bool operator < (const timeval & lhs, const timeval & rhs) {
    if (lhs.tv_sec < rhs.tv_sec) return true;
    if (lhs.tv_sec > rhs.tv_sec) return false;
    return lhs.tv_usec < rhs.tv_usec;
}

static constexpr suseconds_t MILHAO = 1000 * 1000;
timeval operator + (timeval lhs, const size_t mili) {
    lhs.tv_usec += mili * 1000;
    if (lhs.tv_usec > MILHAO) {
        lhs.tv_sec += lhs.tv_usec / MILHAO;
        lhs.tv_usec %= MILHAO;
    }
    return lhs;
}

double operator - (const timeval & lhs, const timeval & rhs) {
    const int dsec = (lhs.tv_sec - rhs.tv_sec) * (int) MILHAO;
    const int dusec = lhs.tv_usec - rhs.tv_usec;
    return (dsec + dusec) / 1000.0;
}

namespace util {
namespace tst {

static void print(const std::string & id,
                  const timeval & val) {
    printf("%15s = %8ld / %8ld\n", id.c_str(), val.tv_sec, val.tv_usec);
}

static void print(const int line,
                  const size_t mili,
                  const timeval & depois,
                  const timeval & fim) {
    printf("\n");
    printf("da linha = %d\n", line);
    printf("tamanho da espera = %zu\n", mili);
    print("depois", depois);
    print("fim", fim);
    printf("diferenca = %lf\n", fim - depois);
}

static void confereEspera(const size_t mili) {
    using namespace std::rel_ops;
    timeval depois;

    Espera esp(mili);
    auto fim = esp.fim();
    for (size_t i = 0; i < 10; ++i) {
        TSM_ASSERT(mili, not esp.expirou());
    }
    esp.espera();
    TSM_ASSERT(mili, esp.expirou());
    gettimeofday(&depois, nullptr);
    TSM_ASSERT(mili, fim <= depois);
    if (fim > depois)
        print(__LINE__, mili, depois, fim);

    esp.zera();
    fim = esp.fim();
    for (size_t i = 0; i < 10; ++i) {
        TSM_ASSERT(mili, not esp.expirou());
    }
    esp.espera();
    TSM_ASSERT(mili, esp.expirou());
    gettimeofday(&depois, nullptr);

    TSM_ASSERT(mili, fim <= depois);
    if (fim > depois)
        print(__LINE__, mili, depois, fim);
}

void TesteEspera::testeEspera() {
    for (size_t i = 0; i < 10; ++i) {
        confereEspera(1);
        confereEspera(10);
        confereEspera(20);
        confereEspera(30);
    }
}

static void confereFim(const size_t mili) {
    using namespace std::rel_ops;
    timeval antes;

    gettimeofday(&antes, nullptr);
    Espera esp(mili);
    auto fim = antes + mili;
    TSM_ASSERT(mili, antes < esp.fim());
    TSM_ASSERT(mili, fim <= esp.fim());

    gettimeofday(&antes, nullptr);
    esp.zera();
    fim = antes + mili;
    TSM_ASSERT(mili, antes < esp.fim());
    TSM_ASSERT(mili, fim <= esp.fim());
}

void TesteEspera::testeFim() {
    for (size_t i = 0; i < 1000; ++i) {
        confereFim(1);
        confereFim(10);
        confereFim(20);
        confereFim(30);
    }
}

}
}
