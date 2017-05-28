
#include "Fonte.h"
#include <algorithm>

namespace gui {

Fonte::Fonte(const std::string & nome,
             const unsigned char tamanho)
    : nome_(nome),
      tamanho_(tamanho) {
}

void Fonte::swap(Fonte & rhs) {
    nome_.swap(rhs.nome_);
    std::swap(tamanho_, rhs.tamanho_);
}

bool operator == (const Fonte & lhs, const Fonte & rhs) {
    return lhs.nome() == rhs.nome()
           && lhs.tamanho() == rhs.tamanho();
}

}
