#pragma once

#include <cstdio>
#include <sys/time.h>

namespace util {
/** Respons�vel garantir que ser� aguardado at� que determinado tempo passe. */
class Espera {
public:
    /**
     * @param milissegundos a quantidade m�nima de tempo em milissegundos a esperar
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
