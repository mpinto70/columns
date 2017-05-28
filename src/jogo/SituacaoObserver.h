
#ifndef SITUACAOOBSERVER_H_mhpa
#define SITUACAOOBSERVER_H_mhpa

#include "jogo/Situacao.h"
#include <memory>

namespace jogo {
/** Interface dos observadores da situação do jogo.
 */
class SituacaoObserver {
    public:
        /** destrutor. */
        virtual ~SituacaoObserver() = default;
        /** será chamado quando houver nova situação.
         * @param situacao a situação atual do jogo.
         */
        virtual void atualiza(const Situacao & situacao) const = 0;
};

/** ponteiro para observador de situação. */
typedef std::unique_ptr<SituacaoObserver> SituacaoObserverPtr;
}

#endif
