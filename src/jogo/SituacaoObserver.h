#pragma once

#include "jogo/Situacao.h"
#include <memory>

namespace jogo {
/** Interface dos observadores da situação do jogo.  */
class SituacaoObserver {
    public:
        virtual ~SituacaoObserver() = default;
        /** será chamado quando houver nova situação.
         * @param situacao a situação atual do jogo.
         */
        virtual void atualiza(const Situacao & situacao) const = 0;
};

typedef std::unique_ptr<SituacaoObserver> SituacaoObserverPtr;
}
