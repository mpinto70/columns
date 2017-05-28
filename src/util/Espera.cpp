
#include "Espera.h"

#include <unistd.h>

namespace util {

Espera::Espera(const size_t milissegundos)
    : microssegundos_(milissegundos * 1000),
      fim_ {0, 0} {
    zera();
}

static constexpr suseconds_t MILHAO = 1000 * 1000;
void Espera::zera() {
    gettimeofday(&fim_, nullptr);
    fim_.tv_usec += microssegundos_;
    if (fim_.tv_usec > MILHAO) {
        const auto sobra = fim_.tv_usec / MILHAO;
        fim_.tv_sec += sobra;
        fim_.tv_usec %= MILHAO;
    }
}

bool Espera::expirou() const {
    timeval t;
    gettimeofday(&t, nullptr);
    if (t.tv_sec > fim_.tv_sec) return true;
    if (t.tv_sec < fim_.tv_sec) return false;
    return (t.tv_usec >= fim_.tv_usec);
}

void Espera::espera() const {
    while (not expirou()) {
        usleep(200);
    }
}

}
