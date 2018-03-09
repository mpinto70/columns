
#include "Fonte.h"
#include <algorithm>

namespace gui {

Fonte::Fonte(const std::string& nome,
      const unsigned char tamanho)
      : nome_(nome),
        tamanho_(tamanho) {
}

bool operator==(const Fonte& lhs, const Fonte& rhs) {
    return lhs.nome() == rhs.nome()
           && lhs.tamanho() == rhs.tamanho();
}

bool operator!=(const Fonte& lhs, const Fonte& rhs) {
    return not(lhs == rhs);
}
}
