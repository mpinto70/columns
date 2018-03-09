#pragma once

#include <cstdio>
#include <sys/time.h>

namespace util {
/** Responsável garantir que será aguardado até que determinado tempo passe. */
class Espera {
public:
    /**
     * @param milissegundos a quantidade mínima de tempo em milissegundos a esperar
     */
    Espera(size_t milissegundos);
    ~Espera() = default;

    void zera();
    bool expirou() const;
    void espera() const;
    const timeval& fim() const { return fim_; }

private:
    size_t microssegundos_; ///< a tempo a esperar
    timeval fim_;           ///< o tempo final
};
}
