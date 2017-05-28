
#ifndef ESPERA_H_mhpa
#define ESPERA_H_mhpa

#include <sys/time.h>
#include <cstdio>

namespace util {
/** Responsável garantir que será aguardado até que determinado tempo passe. */
class Espera {
    public:
        /** cria o objeto
         * @param milissegundos a quantidade mínima de tempo em milissegundos a esperar
         */
        Espera(size_t milissegundos);
        /** destrutor. */
        ~Espera() = default;
        /** zera a contagem de tempo. */
        void zera();
        /** @returns se o tempo já expirou. */
        bool expirou() const;
        /** espera até que o tempo haja passado. */
        void espera() const;
        /** @returns o fim. */
        const timeval & fim() const { return fim_; }
    private:
        size_t microssegundos_;     ///< a tempo a esperar
        timeval fim_;               ///< o tempo final
};

}

#endif
