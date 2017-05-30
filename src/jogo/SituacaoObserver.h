#pragma once

#include "jogo/Situacao.h"
#include <memory>

namespace jogo {
/** Interface dos observadores da situa��o do jogo.  */
class SituacaoObserver {
    public:
        virtual ~SituacaoObserver() = default;
        /** ser� chamado quando houver nova situa��o.
         * @param situacao a situa��o atual do jogo.
         */
        virtual void atualiza(const Situacao & situacao) const = 0;
};

typedef std::unique_ptr<SituacaoObserver> SituacaoObserverPtr;
}
